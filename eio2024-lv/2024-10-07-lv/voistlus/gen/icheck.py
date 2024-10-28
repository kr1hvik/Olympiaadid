#!/usr/bin/env python3

# Input validator

import sys

st = {2, 3, 4}

fi = open(sys.argv[1], 'rt')
fo = open(sys.argv[2], 'wt')

n = int(fi.readline())
if 1 > n or n > 300:
	sys.exit('N out of range')
print(n, file=fo)
if n > 10:
	st.discard(2)
if n > 80:
	st.discard(3)

a = [int(a) for a in fi.readline().split()]
if len(a) != n:
	sys.exit('Wrong length of A')
for i in range(n):
	if 0 > a[i] or a[i] > 1e9:
		sys.exit(f'A[{i}] out of range')
	if i > 0 and not (a[i - 1] > a[i]):
		sys.exit('A not sorted')
print(*a, file=fo)

b = [int(b) for b in fi.readline().split()]
if len(b) != n:
	sys.exit('Wrong length of B')
for i in range(n):
	if 0 > b[i] or b[i] > 1e9:
		sys.exit(f'B[{i}] out of range')
print(*b, file=fo)

fi.close()
fo.close()

if len(sys.argv) > 4 and sys.argv[4] == '-v':
	print('subtasks:', *st)
