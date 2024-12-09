n, K = map(int, input().split())
gs = map(int, input().split())
good = [False] * n
for g in gs:
    good[g - 1] = True

dp = [[[0 for _ in range(n * n + 1)] for __ in range(n + 1)] for ___ in range(n + 1)]
dp[0][0][0] = 1

for i in range(n):
    # try placing i

    for j in range(n - 1, -1, -1):
        for k in range(n - 1, -1, -1):
            for S in range(n * n - i, -1, -1):
                dp[j + 1][k + (not good[i])][S + i] += dp[j][k][S]

if (K * (n - 1)) % 2 == 1:
    print(-1)
    print(0)
else:
    good_S = (K * (n - 1)) // 2
    for k in range(n + 1):
        if dp[K][k][good_S] != 0:
            print(k)
            print(dp[K][k][good_S])
            break
