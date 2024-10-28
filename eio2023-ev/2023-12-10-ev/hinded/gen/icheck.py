#!/usr/bin/env python3

# sisendi korrektsuse kontrollija

import sys

fi = open(sys.argv[1], 'rt')
fo = open(sys.argv[2], 'wt')

n = int(fi.readline())
if 2 > n or n > 300:
	sys.exit('N out of range')
fo.write(f'{n}\n')

for i in range(n):
	a = [int(_) for _ in fi.readline().split()]
	if len(a) != n:
		sys.exit(f'invalid length of A[{1 + i}]')
	for j in range(n):
		if 0 > a[j] or a[j] > 100:
			sys.exit(f'A[{1 + i}][{1 + j}] out of range')
	fo.write(f'{" ".join(str(_) for _ in a)}\n')

fi.close()
fo.close()

if len(sys.argv) > 4 and sys.argv[4] == '-v':
	st = []
	if n <= 12:
		st.append(1)
	if n <= 80:
		st.append(2)
	st.append(3)
	print('subtasks:', *st)
