INF = 10**9 + 5

class State:
    def __init__ (self, steps = INF, ways = 0):
        self.steps = steps
        self.ways = ways

    def merge_from (self, oth):
        if oth.steps < self.steps:
            self.steps = oth.steps
            self.ways = oth.ways
        elif oth.steps == self.steps:
            self.ways += oth.ways

n, K = map(int, input().split())
good = [False] * n
gs = map(int, input().split())
for g in gs:
    good[g - 1] = True

dp = [[State() for _ in range(n * n + 1)] for __ in range(2 * n + 1)]
ndp = [[State() for _ in range(n * n + 1)] for __ in range(2 * n + 1)]

dp[0][0] = State(0, 1)
for i in range(n):
    for j in range(2 * n + 1):
        for k in range(n * n + 1):
            ndp[j][k] = State()
    
    for j in range(-n, n + 1):
        for S in range(0, n * n + 1):
            if dp[j][S].steps == INF:
                continue

            if good[i]:
                # currently occupied

                # do nothing
                if S + i <= n * n:
                    ndp[j][S + i].merge_from(dp[j][S])

                # try removing them
                if j + 1 <= n:
                    ndp[j + 1][S].merge_from(dp[j][S])
            else:
                # currently unoccupied

                # do nothing
                ndp[j][S].merge_from(dp[j][S])

                # try adding something here
                if j - 1 >= -n and S + i <= n * n:
                    ndp[j - 1][S + i].merge_from(State(dp[j][S].steps + 1, dp[j][S].ways))
    dp, ndp = ndp, dp

if (K * (n - 1)) % 2 == 1:
    print(-1)
    print(0)
else:
    good_S = (K * (n - 1)) // 2
    print(dp[0][good_S].steps)
    print(dp[0][good_S].ways)
