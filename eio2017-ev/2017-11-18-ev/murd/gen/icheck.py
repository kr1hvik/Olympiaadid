# sisendi korrektsuse kontrollija

import sys

fi = open(sys.argv[1], 'rt')
fo = open(sys.argv[2], 'wt')

(a, b) = map(int, fi.readline().strip().split('/'))
if 0 > a or a > 1000:
	sys.exit('A out of range')
if 1 > b or b > 1000:
	sys.exit('B out of range')
fo.write('{0}/{1}\n'.format(a, b))

(c, d) = map(int, fi.readline().strip().split('/'))
if 0 > c or c > 1000:
	sys.exit('C out of range')
if 1 > d or d > 1000:
	sys.exit('D out of range')
fo.write('{0}/{1}\n'.format(c, d))

fi.close()
fo.close()
