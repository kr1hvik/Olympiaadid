import sys

n = int(sys.stdin.readline())
grid = [None] * n

tot = 0
for i in range(n):
	grid[i] = [int(_) for _ in sys.stdin.readline().split()]
	for j in range(n):
		grid[i][j] -= 50
		tot += grid[i][j]

sums = [[0 for _ in range(1 + n)] for _ in range(1 + n)]
for i in range(1, 1 + n):
	for j in range(1, 1 + n):
		sums[i][j] = sums[i][j - 1] + sums[i - 1][j] - sums[i - 1][j - 1] + grid[i - 1][j - 1]

best = 0
for i1 in range(1, 1 + n):
	for j1 in range(1, 1 + n):
		for i2 in range(1 + i1):
			for j2 in range(1 + j1):
				sum = sums[i1][j1] - sums[i1][j2] - sums[i2][j1] + sums[i2][j2]
				best = max(best, tot - sum)

sys.stdout.write(f'{best}\n')
