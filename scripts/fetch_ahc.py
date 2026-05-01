#!/usr/bin/env python3
"""
fetch_ahc.py - AHCの問題文取得＋ツール（ビジュアライザ等）自動ダウンロード
Usage: python fetch_ahc.py <contest_number> <out_dir>
"""

import sys
import os
import re
import io
import zipfile
import http.cookiejar
from pathlib import Path

import requests
from bs4 import BeautifulSoup, Tag

COOKIE_PATH = Path(os.environ.get("LOCALAPPDATA", "")) / "online-judge-tools" / "online-judge-tools" / "cookie.jar"


def load_atcoder_cookies() -> dict:
    cookies = {}
    if not COOKIE_PATH.exists():
        return cookies
    jar = http.cookiejar.LWPCookieJar(str(COOKIE_PATH))
    try:
        jar.load(ignore_discard=True, ignore_expires=True)
        for cookie in jar:
            if "atcoder.jp" in cookie.domain:
                cookies[cookie.name] = cookie.value
    except Exception:
        pass
    return cookies


def get(url: str, cookies: dict = {}) -> requests.Response:
    headers = {"User-Agent": "Mozilla/5.0"}
    resp = requests.get(url, headers=headers, cookies=cookies, timeout=30)
    resp.raise_for_status()
    return resp


def find_tool_links(soup: BeautifulSoup) -> dict:
    """ページからツール関連のURLを抽出"""
    links = {}
    for a in soup.find_all("a", href=True):
        href = a["href"]
        if "img.atcoder.jp" not in href:
            continue
        if "_windows.zip" in href:
            links["windows_zip"] = href
        elif href.endswith(".zip"):
            links.setdefault("source_zip", href)
        elif "seeds.txt" in href:
            links["seeds"] = href
        elif ".html" in href and "seed" not in href and "lang" in href:
            base = href.split("?")[0]
            links["web_vis"] = base + "?lang=ja"
    return links


def tag_to_markdown(tag: Tag) -> str:
    if isinstance(tag, str):
        return tag

    result = []
    name = tag.name if hasattr(tag, "name") else None

    if name in ("h1", "h2", "h3", "h4", "h5", "h6"):
        level = int(name[1])
        text = tag.get_text(" ", strip=True)
        result.append(f"\n{'#' * level} {text}\n")
    elif name == "p":
        text = tag.get_text(" ", strip=True)
        if text:
            result.append(f"\n{text}\n")
    elif name in ("ul", "ol"):
        for i, li in enumerate(tag.find_all("li", recursive=False)):
            prefix = f"{i+1}." if name == "ol" else "-"
            result.append(f"{prefix} {li.get_text(' ', strip=True)}")
        result.append("")
    elif name == "table":
        rows = tag.find_all("tr")
        for row_i, row in enumerate(rows):
            cells = row.find_all(["th", "td"])
            line = "| " + " | ".join(c.get_text(" ", strip=True) for c in cells) + " |"
            result.append(line)
            if row_i == 0:
                result.append("| " + " | ".join(["---"] * len(cells)) + " |")
        result.append("")
    elif name == "pre":
        code = tag.get_text()
        result.append(f"\n```\n{code.strip()}\n```\n")
    elif name in ("strong", "b"):
        result.append(f"**{tag.get_text()}**")
    elif name in ("em", "i"):
        result.append(f"*{tag.get_text()}*")
    elif name == "br":
        result.append("  \n")
    elif name in ("div", "section", "span", None):
        for child in tag.children:
            result.append(tag_to_markdown(child))
    else:
        text = tag.get_text(" ", strip=True)
        if text:
            result.append(text)

    return "".join(result)


def build_markdown(soup: BeautifulSoup, contest_id: str, tool_links: dict) -> str:
    upper = contest_id.upper()
    parts = [f"# {upper} 問題文\n"]

    # ツールリンクをヘッダに追記
    if tool_links:
        parts.append("\n## ツール\n")
        if "web_vis" in tool_links:
            parts.append(f"- [Web ビジュアライザ]({tool_links['web_vis']})\n")
        if "windows_zip" in tool_links:
            parts.append(f"- [Windows バイナリ]({tool_links['windows_zip']})\n")
        if "seeds" in tool_links:
            parts.append(f"- [seeds.txt]({tool_links['seeds']})\n")
        parts.append("")

    task_div = soup.find("div", id="task-statement")
    if task_div:
        parts.append(tag_to_markdown(task_div))

    markdown = "\n".join(parts)
    markdown = re.sub(r"\n{3,}", "\n\n", markdown)
    return markdown.strip()


def download_tools(tool_links: dict, out_dir: Path, cookies: dict):
    """Windows zip を tools/ に展開 + seeds.txt をダウンロード"""
    tools_dir = out_dir / "tools"
    tools_dir.mkdir(exist_ok=True)

    if "windows_zip" in tool_links:
        url = tool_links["windows_zip"]
        print(f"Downloading tools zip: {url}", file=sys.stderr)
        resp = get(url, cookies)
        with zipfile.ZipFile(io.BytesIO(resp.content)) as z:
            for member in z.infolist():
                # zip内のトップフォルダ（tools_x86_64-pc-windows-gnu/）を除去して展開
                parts = Path(member.filename).parts
                if len(parts) <= 1:
                    continue
                rel = Path(*parts[1:])
                dest = tools_dir / rel
                if member.is_dir():
                    dest.mkdir(parents=True, exist_ok=True)
                else:
                    dest.parent.mkdir(parents=True, exist_ok=True)
                    dest.write_bytes(z.read(member.filename))
        print(f"  Extracted: {tools_dir}", file=sys.stderr)

    if "seeds" in tool_links:
        url = tool_links["seeds"]
        print(f"Downloading seeds.txt: {url}", file=sys.stderr)
        resp = get(url, cookies)
        seeds_path = tools_dir / "seeds.txt"
        seeds_path.write_bytes(resp.content)
        print(f"  Saved: {seeds_path}", file=sys.stderr)


def main():
    if len(sys.argv) < 3:
        print("Usage: fetch_ahc.py <contest_number> <out_dir>", file=sys.stderr)
        sys.exit(1)

    arg = sys.argv[1].lower().lstrip("ahc")
    num = arg.zfill(3)
    contest_id = f"ahc{num}"
    out_dir = Path(sys.argv[2])
    out_dir.mkdir(parents=True, exist_ok=True)

    cookies = load_atcoder_cookies()
    url = f"https://atcoder.jp/contests/{contest_id}/tasks/{contest_id}_a"
    print(f"Fetching: {url}", file=sys.stderr)
    resp = get(url, cookies)

    soup = BeautifulSoup(resp.text, "html.parser")
    tool_links = find_tool_links(soup)

    # ディレクトリ作成
    (out_dir / "src").mkdir(exist_ok=True)
    problem_dir = out_dir / "problem"
    problem_dir.mkdir(exist_ok=True)
    (problem_dir / "images").mkdir(exist_ok=True)
    markdown = build_markdown(soup, contest_id, tool_links)
    md_path = problem_dir / "statement.md"
    md_path.write_text(markdown, encoding="utf-8")
    print(f"Saved: {md_path}", file=sys.stderr)

    # ツール類をダウンロード
    if tool_links:
        download_tools(tool_links, out_dir, cookies)
    else:
        print("No tool links found on the page.", file=sys.stderr)


if __name__ == "__main__":
    main()
