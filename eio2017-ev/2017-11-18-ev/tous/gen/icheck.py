# sisendi korrektsuse kontrollija

import sys

fi = open(sys.argv[1], 'rt')
fo = open(sys.argv[2], 'wt')

n = int(fi.readline().strip())
if 1 > n or n > 50000:
	sys.exit('N out of range')
fo.write('{0}\n'.format(n))

for i in range(n):
	h = int(fi.readline().strip())
	if 0 > h or h > 1000000:
		sys.exit('H[{0}] out of range'.format(1 + i))
	fo.write('{0}\n'.format(h))

fi.close()
fo.close()

if len(sys.argv) > 3 and sys.argv[3] == '-v':
	if n <= 50:
		print('subtask 1')
	else:
		print('subtask 2')
