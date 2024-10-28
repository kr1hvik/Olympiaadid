import itertools

n = int(input())
a = list(map(int, input().split()))
b = list(map(int, input().split()))
ans = [0] * n
for perm in itertools.permutations(range(n)):
    mx = 0
    for i in range(n):
        mx = max(mx, a[i] + b[perm[i]])
    for i in range(n):
        if a[i] + b[perm[i]] == mx:
            ans[i] += 1
for i in range(n):
    print(ans[i])
