#!/usr/bin/env python3

# sisendi korrektsuse kontrollija

import sys

fi = open(sys.argv[1], 'rt')
fo = open(sys.argv[2], 'wt')

n = int(fi.readline())
if 1 > n or n > 1_000:
	sys.exit('N out of range')
fo.write(f'{n}\n')

s = fi.readline().strip()
if len(s) != n:
	sys.exit('invalid length of S')
for c in s:
	if c not in 'VP':
		sys.exit('invalid characters in S')
fo.write(f'{s}\n')

fi.close()
fo.close()
