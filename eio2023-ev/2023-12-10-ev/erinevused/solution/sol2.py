# efektiivne lahendus: O(N + maxA^2)

# loendab iga võimaliku tulemuse esinemiste arvu sisendis;
# siis vaatab kõiki võimalike tulemuste paare ja liidab
# iga paari elementide vahe summasse nii mitme kordselt,
# kui mitu sellist tulemuste paari sisendi elementidest
# moodustada saab

import sys

piir = 1001 # tulemuste ülempiir

n = int(sys.stdin.readline())
a = [int(_) for _ in sys.stdin.readline().split()]

mitu = [0] * piir
for t in a:
	mitu[t] += 1

s = 0
for t in range(piir):
	for u in range(t):
		s += (t - u) * mitu[t] * mitu[u]

sys.stdout.write(f'{s}\n')
