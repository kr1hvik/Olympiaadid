import sys
import random
import string

m = int(sys.argv[1])
n = int(sys.argv[2])
random.seed(m + n)

print(m, n)
for i in range(n):
	z = []
	for j in range(m):
		k = random.randint(2, 8)
		x = ''.join(random.choices(string.ascii_lowercase[0:2], k=k))
		z.append(x)
	print(*z)
