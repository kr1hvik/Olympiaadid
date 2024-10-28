mod = 1000000007
n = int(input())
a = list(map(int, input().split()))
b = list(map(int, input().split()))
b.sort(reverse=True)
for i in range(n):
    ans = 0
    for j in range(n):
        p = 1
        s = a[i] + b[j]
        l = 0
        for k in range(n):
            if k == i:
                continue
            while l < n and b[n - l - 1] + a[k] <= s:
                l += 1
            p *= l - (l >= n - j) - k + (k > i);
            if p <= 0:
                p = 0
                break
            p %= mod
        ans += p
        ans %= mod
    print(ans)
