n = int(input())

# lauad sorteeritud vasaku serva järgi
lauadv = []
for i in range(n):
	laud = [int(s) for s in input().split()]
	lauadv.append(laud)
lauadv.sort()

# lauad sorteeritud parema serva järgi
lauadp = lauadv.copy()
lauadp.sort(key = lambda laud: laud[2])

# unikaalsed y-koordinaadi väärtused
kordumatud = [laud[1] for laud in lauadv] + [laud[3] for laud in lauadv]
kordumatud = sorted(list(set(kordumatud)))

# lõikude puu ja laisa levitamise puhver
c = 1
while c < len(kordumatud):
	c *= 2
t = [0] * (2 * c + 1)
lz = [0] * (2 * c + 1)

# uuendame lõikude puu tipu k, mille all on lehed i..j
def upd(k, i, j):
    t[k] += lz[k] # lisame väärtuse laisa levitamise puhvrist tipule
    if i < j:
        # kui k pole leht, siis levitame puhvri sisu alluvatele
        lz[2 * k] += lz[k]
        lz[2 * k + 1] += lz[k]
    lz[k] = 0 # tühjendame kasutatud puhvri

# lisame v lõikude puu lehtedele, mis vastavad väärtustele a..b
# praegu oleme järjega tipus k, mille all on lehed i..j
def add(k, i, j, a, b, v):
    upd(k, i, j) # rakendame muutused laisa levitamise puhvrist
    alampiir = kordumatud[i - 1] if i < len(kordumatud) else 1e10
    ulempiir = kordumatud[j] if j < len(kordumatud) else 1e10
    if alampiir >= b or ulempiir <= a:
        # kui a..b on tervenisti väljaspool alampuud
        # siis pole siin midagi teha
        return
    if alampiir >= a and ulempiir <= b:
        # kui a..b katab terve alampuu
        # siis paneme muutuse puhvrisse ootele
        lz[k] += v
        upd(k, i, j)
        return
    # vastasel juhul töötleme kummagi alampuu eraldi
    add(2 * k, i, (i + j) // 2, a, b, v)
    add(2 * k + 1, (i + j) // 2 + 1, j, a, b, v)
    t[k] = max(t[2 * k], t[2 * k + 1])

# käime skaneeriva joonega läbi kõigi laudade vasakud servad
kattuvad = False
p = 0
for i, laud in enumerate(lauadv):
    # eemaldame need lauad, mis lõppevad enne
    while p < i and lauadp[p][2] <= laud[0]:
        add(1, 1, c, lauadp[p][1], lauadp[p][3], -1)
        p += 1
    # lisame laua, mis algab joone peal
    add(1, 1, c, laud[1], laud[3], 1)
    if t[1] > 1:
        kattuvad = True
        break

if kattuvad:
    print("JAH")
else:
    print("EI")
