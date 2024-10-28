# korrektne, aga ebaefektiive lahendus: vaatab läbi kõik laudade paarid
# ja kontrollib iga paari kohta, kas need kaks lauda omavahel kattuvad

# lauda esitab nelik [x1, y1, x2, y2]
def kattuvad(l1, l2):
	if l1[0] >= l2[2]:
		# l1 tervenisti paremal
		return False
	if l2[0] >= l1[2]:
		# l2 tervenisti paremal
		return False
	if l1[1] >= l2[3]:
		# l1 tervenisti kõrgemal
		return False
	if l2[1] >= l1[3]:
		# l2 tervenisti kõrgemal
		return False
	return True

# loeme laudade andmed
n = int(input())
lauad = []
for i in range(n):
    lauad.append([int(s) for s in input().split()])

# leiame vastuse
vastus = False
for i in range(n):
	for j in range(i):
		if kattuvad(lauad[i], lauad[j]):
			vastus = True

# väljastame vastuse
if vastus:
    print("JAH")
else:
    print("EI")
