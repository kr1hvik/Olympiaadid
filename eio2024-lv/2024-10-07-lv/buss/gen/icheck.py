#!/usr/bin/env python3

# Input validator

import sys

st = {2, 3, 4}

fi = open(sys.argv[1], 'rt')
fo = open(sys.argv[2], 'wt')

h0, m0 = [int(_) for _ in fi.readline().split()]
if 0 > h0 or h0 > 23:
	sys.exit('H out of range')
if 0 > m0 or m0 > 59:
	sys.exit('M out of range')
fo.write(f'{h0} {m0}\n')
t0 = 60 * h0 + m0
if h0 != 0 or m0 != 0:
	st.discard(3)

n = int(fi.readline())
if 1 > n or n > 1000:
	sys.exit('N out of range')
fo.write(f'{n}\n')
if n > 10:
	st.discard(2)
if n > 100:
	st.discard(3)

t1 = t0
for i in range(1, 1 + n):
	h, m, j = [int(_) for _ in fi.readline().split()]
	if 0 > h or h > 23:
		sys.exit(f'H[{i}] out of range')
	if 0 > m or m > 59:
		sys.exit(f'M[{i}] out of range')
	if 0 > j or j > 10_000:
		sys.exit(f'J[{i}] out of range')
	fo.write(f'{h} {m} {j}\n')
	t = 60 * h + m
	if t < t1:
		sys.exit('Route out of order')
	t1 = t
	if h != h0:
		st.discard(2)

fi.close()
fo.close()

if len(sys.argv) > 4 and sys.argv[4] == '-v':
	print('subtasks:', *st)
