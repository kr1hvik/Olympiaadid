# genereerib juhusliku jada

import sys
import random

n = int(sys.argv[1])
m = int(sys.argv[2])

random.seed(n * m)

print n
for i in range(n):
	print random.randint(0, m)
