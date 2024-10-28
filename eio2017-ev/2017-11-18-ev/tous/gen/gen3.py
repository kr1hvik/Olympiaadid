# genereerib vaheldumisi kasvavaid ja kahanevaid jadasid

import sys
import random

k = int(sys.argv[1])
n = int(sys.argv[2])
m = int(sys.argv[3])

random.seed(k * n * m)

print k * n
h = 0
for i in range(k):
	if i & 1 == 0:
		# kasvav h -> m
		for j in range(n):
			h = random.randint(h, max(h, m - (n - j)))
			print h
	else:
		# kahanev h -> 0
		for j in range(n):
			h = random.randint(max(0, 0 + (n - j)), h)
			print h
