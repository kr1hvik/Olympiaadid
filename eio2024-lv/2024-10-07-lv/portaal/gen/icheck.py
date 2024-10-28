#!/usr/bin/env python3

# Input validator

import sys

fi = open(sys.argv[1], 'rt')
fo = open(sys.argv[2], 'wt')

st = {2, 3, 4, 5, 6, 7, 8}

n, m = [int(s) for s in fi.readline().split()]
if 1 > n * m or n * m > 1e5:
	sys.exit('N*M out of range')
fo.write(f'{n} {m}\n')

y, x = [int(s) for s in fi.readline().split()]
if 1 > y or y > n:
	sys.exit('Y out of range')
if 1 > x or x > m:
	sys.exit('X out of range')
fo.write(f'{y} {x}\n')

g = []
for i in range(n):
	s = fi.readline().strip()
	if len(s) != m:
		sys.exit(f'G[{1 + i}] has wrong length')
	for c in s:
		if c not in ['.', '#']:
			sys.exit(f'G[{1 + i}] contains invalid characters')
	fo.write(f'{s}\n')
	g.append(s)

if g[y - 1][x - 1] != '.':
	sys.exit('Start in blocked cell')

c = int(fi.readline().strip())
if 1 > c or c > 1e5:
	sys.exit('C out of range')
fo.write(f'{c}\n')

for i in range(c):
	y, x, w = [int(s) for s in fi.readline().split()]
	if 1 > y or y > n:
		sys.exit(f'Y[{1 + i}] out of range')
	if 1 > x or x > m:
		sys.exit(f'X[{1 + i}] out of range')
	if 1 > w or w > 1e9:
		sys.exit(f'W[{1 + i}] out of range')
	if g[y - 1][x - 1] != '.':
		sys.exit('Coin {1 + i} in blocked cell')
	fo.write(f'{y} {x} {w}\n')

k = int(fi.readline().strip())
if 1 > k or k > 1e5:
	sys.exit('K out of range')
fo.write(f'{k}\n')

if k != 1:
	st.discard(2)
if k != 2:
	st.discard(3)
if k > 4:
	st.discard(4)
if k > 8:
	st.discard(5)
if k > 16:
	st.discard(6)
if k > 1000:
	st.discard(7)

a = [int(s) for s in fi.readline().split()]
if sorted(a) != list(range(1, 1 + k)):
	sys.exit('A not a permutation of 1..K')
fo.write('{}\n'.format(' '.join(str(v) for v in a)))

if a != [2, 1]:
	st.discard(3)

for i in range(k):
	u, v = [int(s) for s in fi.readline().split()]
	if 1 > u or u > n:
		sys.exit(f'U[{1 + i}] out of range')
	if 1 > v or v > m:
		sys.exit(f'V[{1 + i}] out of range')
	if g[u - 1][v - 1] != '.':
		sys.exit('Portal {1 + i} in blocked cell')
	fo.write(f'{u} {v}\n')

fi.close()
fo.close()

if len(sys.argv) > 4 and sys.argv[4] == '-v':
	print('subtasks:', *st)
