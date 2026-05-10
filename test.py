N,K=map(int,input().split())
A=list(map(int,input().split()))

def check(idx,target):
    if idx==N:
        return target==0
    return check(idx+1,target) or check(idx+1,target-A[idx])

if check(0,K):
    print("Yes")
else:
    print("No")