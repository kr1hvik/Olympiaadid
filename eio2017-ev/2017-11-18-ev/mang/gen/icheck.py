# sisendi korrektsuse kontrollija

import sys

fi = open(sys.argv[1], 'rt')
fo = open(sys.argv[2], 'wt')

n = int(fi.readline().strip())
if 1 > n or n > 1000:
	sys.exit('N out of range')
fo.write('{0}\n'.format(n))

aa = map(int, fi.readline().strip().split())
if len(aa) <> n:
	sys.exit('Wrong number of A[] values')
for i, a in enumerate(aa):
	if -n >= a or a >= n:
		sys.exit('A[{0}] out of range'.format(i + 1))
	if i == 0 and a != 0:
		sys.exit('A[{0}] out of range'.format(i + 1))
fo.write('{0}\n'.format(' '.join(map(str, aa))))

fi.close()
fo.close()
