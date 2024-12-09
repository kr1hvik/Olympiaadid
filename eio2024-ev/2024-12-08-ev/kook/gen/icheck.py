#!/usr/bin/env python3

# Input validator

import sys

st = {2, 3, 4, 5}

fi = open(sys.argv[1], 'rt')
fo = open(sys.argv[2], 'wt')

n = int(fi.readline())
if 1 > n or n > 100_000:
	sys.exit('N out of range')
print(n, file=fo)
if n != 2:
	st.discard(2)
if n > 1_000:
	st.discard(4)

p = [int(x) for x in fi.readline().split()]
if len(p) != n:
	sys.exit('Invalid length of P')
for i in range(n):
	if 1 > p[i] or p[i] > 1_000:
		sys.exit(f'P[{1 + i}] out of range')
print(*p, file=fo)
if p != sorted(p):
	st.discard(3)

m = [int(x) for x in fi.readline().split()]
if len(m) != n:
	sys.exit('Invalid length of M')
for i in range(n):
	if 1 > m[i] or m[i] > 1_000:
		sys.exit(f'M[{1 + i}] out of range')
print(*m, file=fo)
if m != sorted(m):
	st.discard(3)

fi.close()
fo.close()

if len(sys.argv) > 4 and sys.argv[4] == '-v':
	print('subtasks:', *st)
