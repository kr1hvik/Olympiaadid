#!/usr/bin/env python3

# Input validator

import sys

fi = open(sys.argv[1], 'rt')
fo = open(sys.argv[2], 'wt')

st = {2, 3, 4}

m, n, x1, y1, x2, y2 = (int(x) for x in fi.readline().split())
if 1 > m or m > 500:
	sys.exit('M out of range')
if 1 > n or n > 500:
	sys.exit('N out of range')
if 0 > x1 or x1 > m:
	sys.exit('X1 out of range')
if 0 > y1 or y1 > n:
	sys.exit('Y1 out of range')
if 0 > x2 or x2 > m:
	sys.exit('X2 out of range')
if 0 > y2 or y2 > n:
	sys.exit('Y2 out of range')
if x1 != 0 and x1 != m and y1 != 0 and y1 != n:
	sys.exit('(X1, Y1) not on edge')
if x2 != 0 and x2 != m and y2 != 0 and y2 != n:
	sys.exit('(X2, Y2) not on edge')
if x1 == x2:
	if x1 == 0 or x1 == m:
		sys.exit('line on edge')
	if not (y1 == 0 and y2 == n or y1 == n and y2 == 0):
		sys.exit('line not edge to edge')
elif y1 == y2:
	if y1 == 0 or y1 == n:
		sys.exit('line on edge')
	if not (x1 == 0 and x2 == m or x1 == m and x2 == 0):
		sys.exit('line not edge to edge')
else:
	if abs(x1 - x2) != abs(y1 - y2):
		sys.exit('line not at 45 degrees')
fo.write(f'{m} {n} {x1} {y1} {x2} {y2}\n')

if not (x1 == x2 or y1 == y2):
	st.remove(2)
if (x1 == 0 and x2 == m or x1 == m and x2 == 0) and y1 not in [0, y2, n] and y2 not in [0, y1, n]:
	st.remove(3)
if (y1 == 0 and y2 == n or y1 == n and y2 == 0) and x1 not in [0, x2, m] and x2 not in [0, x1, m]:
	st.remove(3)

fi.close()
fo.close()

if len(sys.argv) > 4 and sys.argv[4] == '-v':
	print('subtasks:', *st)
