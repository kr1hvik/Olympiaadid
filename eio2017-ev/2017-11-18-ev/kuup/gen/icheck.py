# sisendi korrektsuse kontrollija

import sys

fi = open(sys.argv[1], 'rt')
fo = open(sys.argv[2], 'wt')

s = set()

for i in range(6):
	(x, y) = map(int, fi.readline().strip().split())
	if 1 > x or x > 10:
		sys.exit('X out of range')
	if 1 > y or y > 10:
		sys.exit('Y out of range')
	if (x, y) in s:
		sys.exit('duplicate square')
	s.add((x, y))
	fo.write('{0} {1}\n'.format(x, y))

fi.close()
fo.close()
