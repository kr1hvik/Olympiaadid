# sisendi korrektsuse kontrollija

import sys

fi = open(sys.argv[1], 'rt')
fo = open(sys.argv[2], 'wt')

t = int(fi.readline())
if 1 > t or t > 20:
	sys.exit('T out of range')
fo.write(f'{t}\n')

maxn = 0
maxs = 0
for i in range(t):
	n = int(fi.readline())
	if 2 > n or n > 10:
		sys.exit(f'N out of range in test case {1 + i}')
	s = fi.readline().strip()
	if len(s) == 0 or len(s) % n != 0 or n**(len(s) / n) > 2e7:
		sys.exit(f'Invalid length of S in test case {1 + i}')
	for c in s:
		if 'a' > c or c > 'z':
			sys.exit(f'Invalid characters in S in test case {1 + i}')
	fo.write(f'{n}\n')
	fo.write(f'{s}\n')
	maxn = max(maxn, n)
	maxs = max(maxs, len(s))

fi.close()
fo.close()

if len(sys.argv) > 4 and sys.argv[4] == '-v':
	st = []
	if maxn == 2 and maxs <= 2*11:
		st.append(1)
	if maxn == 2:
		st.append(2)
	st.append(3)
	print('subtasks:', *st)
