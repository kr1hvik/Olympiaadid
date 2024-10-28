mod = 1000000007
n = int(input())
a = list(map(int, input().split()))
b = list(map(int, input().split()))
for i in range(n):
    ans = 0
    for j in range(n):
        p = 1
        s = a[i] + b[j]
        l = 0
        for k in range(n):
            if k == i:
                continue
            q = 0
            for l in range(n):
                if l == j:
                    continue
                if a[k] + b[l] <= s:
                    q += 1
            if k < i:
                q -= k
            else:
                q -= k - 1
            p *= max(q, 0)
            p %= mod
        ans += p
        ans %= mod
    print(ans)
