#!/usr/bin/env python3

# Input validator

import sys
import re

colors = re.compile('[a-z]{1,20}')
basic = {'punane', 'kollane', 'roheline', 'sinine'}

st = {2, 3, 4}

fi = open(sys.argv[1], 'rt')
fo = open(sys.argv[2], 'wt')

n = int(fi.readline())
if 1 > n or n > 100000:
	sys.exit('N out of range')
fo.write(f'{n}\n')
if n > 1000:
	st.discard(3)

for i in range(n):
	c = fi.readline().strip()
	if not colors.match(c):
		sys.exit(f'Invalid color {c}')
	if c not in basic:
		st.discard(2)
	fo.write(f'{c}\n')

fi.close()
fo.close()

if len(sys.argv) > 4 and sys.argv[4] == '-v':
	print('subtasks:', *st)
