import sys
import random
import string

m = int(sys.argv[1])
n = int(sys.argv[2])
r = int(sys.argv[3]);
random.seed(m + n + r)

w = []
for i in range(r):
	k = random.randint(30, 80)
	x = ''.join(random.choices(string.ascii_lowercase, k=k))
	w.append(x)

print(m, n)
for i in range(n):
	z = []
	for j in range(m):
		x = random.choice(w)
		x += ''.join(random.choices(string.ascii_lowercase, k=10))
		z.append(x)
	print(*z)
