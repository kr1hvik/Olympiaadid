#!/usr/bin/env python3

# sisendi korrektsuse kontrollija

import sys

fi = open(sys.argv[1], 'rt')
fo = open(sys.argv[2], 'wt')

n = int(fi.readline())
if 1 > n or n > 50_000:
	sys.exit('N out of range')
fo.write(f'{n}\n')

a = [int(_) for _ in fi.readline().split()]
if len(a) != n:
	sys.exit('invalid length of A')
for i in range(n):
	if 0 > a[i] or a[i] > 10_000_000:
		sys.exit(f'A[{1 + i}] out of range')
fo.write(f'{" ".join(str(_) for _ in a)}\n')

k = len(set(a)) # unikaalseid numbreid sisendis
m = max(a) - min(a) + 1 - k
if m > 50_000:
	sys.exit('M out of range')

fi.close()
fo.close()

if len(sys.argv) > 4 and sys.argv[4] == '-v':
	if k < n:
		print('duplicates')
	st = []
	if a == sorted(a) and k == n:
		st.append(1)
	st.append(2)
	print('subtasks:', *st)
