param(
    [Parameter(Mandatory=$true)]
    [string]$Source
)
$here = Split-Path -Parent $MyInvocation.MyCommand.Path
$inc = Join-Path $here "..\vendor\ac-library"
g++ -std=c++17 -O2 -I "$inc" -I "$PWD" -o "${Source%.*}.exe" $Source
Write-Output "Built ${Source%.*}.exe"
