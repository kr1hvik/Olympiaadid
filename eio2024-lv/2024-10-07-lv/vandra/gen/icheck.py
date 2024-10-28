#!/usr/bin/env python3

# Input validator

import sys

st = {2, 3, 4}

fi = open(sys.argv[1], 'rt')
fo = open(sys.argv[2], 'wt')

n = int(fi.readline())
if 1 > n or n > 1e5:
	sys.exit('N out of range')
fo.write(f'{n}\n')
if n > 1e3:
	st.discard(2)

lv, rv, bh, th = [], [], [], []
for i in range(n):
	x1, y1, x2, y2 = [int(_) for _ in fi.readline().split()]
	if 0 > x1 or x1 >= x2 or x2 > 1e9:
		sys.exit(f'X[{i}] out of range')
	if 0 > y1 or y1 >= y2 or y2 > 1e9:
		sys.exit(f'Y[{i}] out of range')
	fo.write(f'{x1} {y1} {x2} {y2}\n')
	lv.append((x1, y1, y2))
	rv.append((x2, y1, y2))
	bh.append((y1, x1, x2))
	th.append((y2, x1, x2))

def unify(ll):
	t = []
	ll.sort()
	a, b1, b2 = ll[0]
	for c, d1, d2 in ll:
		if c > a or d1 > b2:
			t.append((a, b1, b2))
			a, b1, b2 = c, d1, d2
		else:
			b2 = d2
	t.append((a, b1, b2))
	ll[:] = t

def touch(l1, l2):
	unify(l1); unify(l2)
	i1, i2 = 0, 0
	while i1 < len(l1) and i2 < len(l2):
		a, b1, b2 = l1[i1]
		c, d1, d2 = l2[i2]
		if a < c or a == c and b2 < d1:
			i1 += 1
			continue
		if c < a or c == a and d2 < b1:
			i2 += 1
			continue
		return True
	return False

if touch(lv, rv) or touch(bh, th):
	st.discard(3)

fi.close()
fo.close()

if len(sys.argv) > 4 and sys.argv[4] == '-v':
	print('subtasks:', *st)
