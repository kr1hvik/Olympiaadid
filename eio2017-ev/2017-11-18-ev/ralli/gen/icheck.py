# sisendi korrektsuse kontrollija

import sys

fi = open(sys.argv[1], 'rt')
fo = open(sys.argv[2], 'wt')

(v, e, q) = map(int, fi.readline().strip().split())
if 1 > v or v > 100000:
	sys.exit('V out of range')
if 1 > e or e > 300000:
	sys.exit('V out of range')
if 1 > q or q > 100000:
	sys.exit('Q out of range')
fo.write('{0} {1} {2}\n'.format(v, e, q))

for i in range(e):
	(a, b) = map(int, fi.readline().strip().split())
	if 1 > a or a > v:
		sys.exit('A[{0}] out of range'.format(1 + i))
	if 1 > b or b > v:
		sys.exit('B[{0}] out of range'.format(1 + i))
	fo.write('{0} {1}\n'.format(a, b))

for i in range(q):
	(a, b) = map(int, fi.readline().strip().split())
	if 1 > a or a > v:
		sys.exit('P[{0}] out of range'.format(1 + i))
	if 1 > b or b > v:
		sys.exit('Q[{0}] out of range'.format(1 + i))
	fo.write('{0} {1}\n'.format(a, b))

fi.close()
fo.close()

if len(sys.argv) > 3 and sys.argv[3] == '-v':
	if v <= 30 and e <= 30:
		print('subtask 1')
	elif q == 1 and v <= 1000 and e <= 1000:
		print('subtask 2')
	else:
		print('subtask 3')
