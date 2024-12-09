import sys
import random
import string

m = int(sys.argv[1])
n = int(sys.argv[2])
ad = sys.argv[3]
random.seed(m + n + hash(ad))

print(m, n)
for i in range(n):
	z = []
	for j in range(m - 1):
		k = random.randint(2, 8)
		x = ''.join(random.choices(string.ascii_lowercase[0:3], k=k))
		z.append(x)
	k = random.randint(2, 8)
	z.append(ad + ''.join(random.choices(string.ascii_lowercase[0:3], k=k)))
	random.shuffle(z)
	print(*z)
