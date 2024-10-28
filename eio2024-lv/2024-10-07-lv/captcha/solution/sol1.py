pildid = [] # nõutav piltide järjekord
klikid = [] # tegelik piltide järjekord; ainult numbritega pildid

# klikib antud pildil
def klikk(pilt):
    if pilt in klikid:
        # pildil juba on number, uuesti klikkimine eemaldab selle
        klikid.remove(pilt)
    else:
        # pildil veel ei ole numbrit, lisame nummerdatud nimekirja lõppu
        klikid.append(pilt)

# loeme nõutava järjekorra
for _ in range(5):
	pildid.append(input())

# loeme ja simuleerime väikevenna klikid
n = int(input())
for _ in range(n):
	klikk(input())

# loome Juku klikkide logi
logi = []
i = 0
# kõigepealt eemaldame need pildid, millel on vale number
while i < len(klikid):
    if klikid[i] == pildid[i]:
        # number i on juba õige pildi juures, liigume järgmisele
        i += 1
    else:
        # number i on vale pildi juures, kustutamiseks peab Juku sellel klikkima
        logi.append(klikid[i])
        klikk(klikid[i])
# seejärel lisame kõik, millel veel numbrit pole
logi += pildid[i : ]

# väljastame vastuse
print(len(logi))
for pilt in logi:
    print(pilt)
