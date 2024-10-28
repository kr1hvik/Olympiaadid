import sys

n = int(sys.stdin.readline())
grid = [None] * n

tot = 0
for i in range(n):
	grid[i] = [int(_) for _ in sys.stdin.readline().split()]
	for j in range(n):
		grid[i][j] -= 50
		tot += grid[i][j]

best = 0
for i1 in range(n):
	for i2 in range(i1, n):
		for j1 in range(n):
			for j2 in range(j1, n):
				sum = 0
				for i3 in range(i1, i2 + 1):
					for j3 in range(j1, j2 + 1):
						sum += grid[i3][j3]
				best = max(best, tot - sum)

sys.stdout.write(f'{best}\n')
