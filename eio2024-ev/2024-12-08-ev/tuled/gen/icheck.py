#!/usr/bin/env python3

# Input validator

import sys

st = {2, 3}

fi = open(sys.argv[1], 'rt')
fo = open(sys.argv[2], 'wt')

x = int(fi.readline())
if 1 > x or x > 1_000:
	sys.exit('X out of range')
print(x, file=fo)

y = int(fi.readline())
if 1 > y or y > 1_000:
	sys.exit('Y out of range')
print(y, file=fo)

n = int(fi.readline())
if 1 > n or n > 100:
	sys.exit('N out of range')
print(n, file=fo)

n *= 100
if 4 * x + 5 * y < n:
	v = 9
elif x < y:
	v = n / x if 4 * x > n else 4 + (n - 4 * x) / y
else:
	v = n / y if 5 * y > n else 5 + (n - 5 * y) / x
if v != round(v):
	st.remove(2)

fi.close()
fo.close()

if len(sys.argv) > 4 and sys.argv[4] == '-v':
	print('subtasks:', *st)
