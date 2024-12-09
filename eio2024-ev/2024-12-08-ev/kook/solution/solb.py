# selgituse koodinäitede testimiseks

n = int(input())
p = [int(x) for x in input().split()]
m = [int(x) for x in input().split()]

p = sorted((x, i) for i, x in enumerate(p))
m = sorted((x, i) for i, x in enumerate(m))

saab = True
for i in range(1, n):
  if m[i][0] * p[0][0] != m[0][0] * p[i][0]:
    saab = False

if saab:
  print('JAH')
  a = [(m[i][1], p[i][1]) for i in range(n)]
  print(*(p + 1 for m, p in sorted(a)))
else:
  print('EI')
