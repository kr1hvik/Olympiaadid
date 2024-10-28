#!/usr/bin/env python3

# Input validator

import sys
import re

id = re.compile('[A-Z]{1,10}')

st = {2, 3, 4}

fi = open(sys.argv[1], 'rt')
fo = open(sys.argv[2], 'wt')

pics = set()
for i in range(5):
	s = fi.readline().strip()
	if not id.match(s):
		sys.exit(f'Invalid picture id {s}')
	if s in pics:
		sys.exit(f'Duplicate picture id {s}')
	pics.add(s)
	fo.write(f'{s}\n')

n = int(fi.readline())
if 0 > n or n > 10:
	sys.exit('N out of range')
fo.write(f'{n}\n')
if n > 1:
	st.discard(2)

clicks = set()
for i in range(n):
	s = fi.readline().strip()
	if s not in pics:
		sys.exit(f'Unknown picture id {s}')
	if s in clicks:
		st.discard(3)
	clicks.add(s)
	fo.write(f'{s}\n')

fi.close()
fo.close()

if len(sys.argv) > 4 and sys.argv[4] == '-v':
	print('subtasks:', *st)
