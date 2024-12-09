#!/usr/bin/env python3

# Input validator

import sys
import re

pat = re.compile('[a-z]{1,100}')

st = {2, 3, 4, 5, 6}

fi = open(sys.argv[1], 'rt')
fo = open(sys.argv[2], 'wt')

m, n = (int(x) for x in fi.readline().split())
if 1 > m or m > 1_000:
	sys.exit('M out of range')
if 1 > n or n > 100_000:
	sys.exit('N out of range')
print(m, n, file=fo)
if m != 1 or n > 10:
	st.discard(2)
if m != 2 or n > 10:
	st.discard(3)

s = 0
for i in range(n):
	words = fi.readline().split()
	for w in words:
		if not pat.match(w):
			sys.exit(f'Invalid word {w} on line {2 + i}')
		s += len(w) + 1
	print(*words, file=fo)
if s > 4_000:
	st.discard(4)
if s > 1_000_000:
	st.discard(5)

fi.close()
fo.close()

if len(sys.argv) > 4 and sys.argv[4] == '-v':
	print('subtasks:', *st)
