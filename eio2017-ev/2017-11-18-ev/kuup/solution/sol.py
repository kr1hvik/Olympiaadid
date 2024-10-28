#!/usr/bin/python2.7
# -*- coding: utf8 -*-

with open("kuupsis.txt", 'r') as fin:
    kuubiruudud = [ (int(rida[0]), int(rida[1])) for rida in [ rida.split(' ') for rida in fin.read().split('\n') if rida ] ]

# Kuubi servad:
# alumisel kihil paripaeva alustades S 0 1 2 3
# ylemisel kihil paripaeva alustades S 4 5 6 7
# kyljed alustades SW 8 9 10 11

ruudunaabrid = [ [-1]*4 for i in range(6) ]

for i in range(6):
    for j in range(6):
        if i == j:
            continue
        if kuubiruudud[i][1]-1 == kuubiruudud[j][1] and kuubiruudud[i][0] == kuubiruudud[j][0]:
            ruudunaabrid[i][0] = j
        elif kuubiruudud[i][0]+1 == kuubiruudud[j][0] and kuubiruudud[i][1] == kuubiruudud[j][1]:
            ruudunaabrid[i][1] = j
        elif kuubiruudud[i][1]+1 == kuubiruudud[j][1] and kuubiruudud[i][0] == kuubiruudud[j][0]:
            ruudunaabrid[i][2] = j
        elif kuubiruudud[i][0]-1 == kuubiruudud[j][0] and kuubiruudud[i][1] == kuubiruudud[j][1]:
            ruudunaabrid[i][3] = j

adj_ruudud = [ [] for i in range(12) ]

suund_to_ilmakaar = ['S', 'E', 'N', 'W']

paripaeva_kyljed = {(0,'D'): ('F',[8,4,9]),
                    (0,'F'): ('D',[1,2,3]),
                    (1,'D'): ('R',[9,5,10]),
                    (1,'R'): ('D',[2,3,0]),
                    (2,'D'): ('B',[10,6,11]),
                    (2,'B'): ('D',[3,0,1]),
                    (3,'D'): ('L',[11,7,8]),
                    (3,'L'): ('D',[0,1,2]),
                    (4,'U'): ('F',[9,0,8]),
                    (4,'F'): ('U',[7,6,5]),
                    (5,'U'): ('R',[10,1,9]),
                    (5,'R'): ('U',[4,7,6]),
                    (6,'U'): ('B',[11,2,10]),
                    (6,'B'): ('U',[5,4,7]),
                    (7,'U'): ('L',[8,3,11]),
                    (7,'L'): ('U',[6,5,4]),
                    (8,'L'): ('F',[4,9,0]),
                    (8,'F'): ('L',[3,11,7]),
                    (9,'R'): ('F',[0,8,4]),
                    (9,'F'): ('R',[5,10,1]),
                    (10,'R'): ('B',[6,11,2]),
                    (10,'B'): ('R',[1,9,5]),
                    (11,'L'): ('B',[2,10,6]),
                    (11,'B'): ('L',[7,8,3])}

x,y = kuubiruudud[0]
vaadatud_ruudud = [True, False, False, False, False, False]
maaratud_tahud = {'D': 0, 'F': -1, 'B': -1, 'L': -1, 'R': -1, 'U': -1}
frontier = [(0, 0, 'D', 0, [1,2,3])]

cannot_fold = False

while frontier != []:
    # Tee kindlaks ruut, millest jutt (arv)
    # Tee kindlaks ilmakaar, kust laheneme (SENW)
    # Tee kindlaks tahk, mida maarame (DBFRLU)
    # Tee kindlaks serv, kus laheneme (0-11)
    # Leia jargmised servad (paripaeva_kyljed)
    sq, from_dir, side, edge, next_edges = frontier[0]
    frontier = frontier[1:]
    next_edges = [edge] + next_edges
    # Pane jargmised servad vastavusse ilmakaartega
    edge_dir = [ (next_edges[i], (i+from_dir)%4) for i in range(4) ]
    # Leia iga serva jaoks, kas sealpool ruudust asub naaber (ruudunaabrid)
    for e, d in edge_dir:
        if ruudunaabrid[sq][d] != -1:
            naaber = ruudunaabrid[sq][d]
            neighside, neighedges = paripaeva_kyljed[(e,side)]
            # Kontrolli, kas seda naabrit on juba kontrollitud (vaadatud_ruudud)
            if vaadatud_ruudud[naaber]:
                # Kontrolli, kas praegu maaratud tahk oleks sama, mis eelnevalt maaratud (maaratud_tahud)
                if maaratud_tahud[neighside] != naaber:
                    cannot_fold = True
                    break
            else:
                # Vaata, kas maaratav tahk on maaramiseks vaba (maaratud_tahud)
                if maaratud_tahud[neighside] != -1:
                    cannot_fold = True
                    break
                # Maara tahk ja lisa uus ruut, tahk, serv, ilmakaar frontieri
                maaratud_tahud[neighside] = naaber
                vaadatud_ruudud[naaber] = True
                frontier.append((naaber, (d+2)%4, neighside, e, neighedges))
        else:
            adj_ruudud[e].append((sq,d))
    if cannot_fold:
        break

with open("kuupval.txt", 'w') as fout:
    if cannot_fold or (-1 in maaratud_tahud.values()):
        fout.write("EI\n")
    else:
        fout.write("JAH\n")
        for i in range(12):
            if adj_ruudud[i]:
                sq, d = adj_ruudud[i][0]
                x,y = kuubiruudud[sq]
                fout.write(str(x)+' '+str(y)+' '+suund_to_ilmakaar[d]+'\n')
