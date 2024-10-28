#!/usr/bin/env python3

import sys, random

n = int(sys.argv[1]) # N
m = int(sys.argv[2]) # max allowed A[i]
s = int(sys.argv[3]) # 0 / 1 = sort / shuffle output
u = int(sys.argv[4]) # number of unique values

random.seed(n + m + s + u)

a = random.sample(range(m + 1), k = u)
a += random.choices(a, k = n - u)

if s == 0:
	a.sort()
if s == 1:
	random.shuffle(a)

print(n)
print(*a)
