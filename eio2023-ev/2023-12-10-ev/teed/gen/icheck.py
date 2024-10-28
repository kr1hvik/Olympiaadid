# sisendi korrektsuse kontrollija

import sys

fi = open(sys.argv[1], 'rt')
fo = open(sys.argv[2], 'wt')

for i in range(3):
	n = int(fi.readline())
	if 0 > n or n > 100:
		sys.exit('Value out of range')
	fo.write(f'{n}\n')

fi.close()
fo.close()
