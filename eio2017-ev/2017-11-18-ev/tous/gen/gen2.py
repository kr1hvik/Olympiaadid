# genereerib monotoonselt kasvava jada

import sys
import random

n = int(sys.argv[1])
m = int(sys.argv[2])

random.seed(n * m)

print n
h = 0
for i in range(n):
	h = random.randint(h, m - (n - i))
	print h
