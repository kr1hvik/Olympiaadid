#!/usr/bin/env python3

# sisendi korrektsuse kontrollija

import sys

fi = open(sys.argv[1], 'rt')
fo = open(sys.argv[2], 'wt')

n = int(fi.readline())
if 2 > n or n > 100_000:
	sys.exit('N out of range')
fo.write(f'{n}\n')

a = [int(_) for _ in fi.readline().split()]
if len(a) != n:
	sys.exit('invalid length of A')
for i in range(n):
	if 0 > a[i] or a[i] > 1_000:
		sys.exit(f'A[{1 + i}] out of range')
fo.write(f'{" ".join(str(_) for _ in a)}\n')

fi.close()
fo.close()

if len(sys.argv) > 4 and sys.argv[4] == '-v':
	st = []
	if n <= 1_000:
		st.append(1)
	if a == sorted(a):
		st.append(2)
	st.append(3)
	print('subtasks:', *st)
