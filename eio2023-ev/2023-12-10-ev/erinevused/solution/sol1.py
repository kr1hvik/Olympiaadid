# efektiivne lahendus: sorteerimine on O(N*log(N)), ülejäänu O(N)

# põhineb tähelepanekul, et iga a[i] esineb lõppsummas plussmärgiga
# nii palju kordi, kui palju on selliseid a[j], mis on temast väiksemad,
# ja miinusmärgiga nii palju kordi, kui palju on temast suuremaid a[j]

# a[] sorteerimise järel on elemendist a[i] väiksemad temast vasakul
# ja suuremad temast paremal

# igast omavahel võrdsete elementide paarist läheb üks summasse pluss-
# ja teine miinusmärgiga, mis annab ka õige tulemuse

import sys

n = int(sys.stdin.readline())
a = [int(_) for _ in sys.stdin.readline().split()]

a.sort()

s = 0
for i in range(n):
	s += a[i] * i
	s -= a[i] * (n - 1 - i)

sys.stdout.write(f'{s}\n')
