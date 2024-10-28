with open("mangsis.txt", 'r') as fin:
    t = fin.read().split('\n')

N = int(t[0])
ruudud = [ int(x) for x in t[1].split(' ') ]
sattumised = [0]*N

frontier = [0]
i = 0
frontier_length = 1
sattumised[0] = 1
while i < frontier_length:
    ruut = frontier[i]
    i += 1
    if ruudud[ruut] == 0:
        for j in range(ruut+1, ruut+7):
            uusruut = j%N
            if sattumised[uusruut] == 0:
                sattumised[uusruut] = 1
                frontier.append(uusruut)
                frontier_length += 1
    else:
        uusruut = ruut+ruudud[ruut]
        if sattumised[uusruut] == 0:
            sattumised[uusruut] = 1
            frontier.append(uusruut)
            frontier_length += 1

with open("mangval.txt", 'w') as fout:
    fout.write(' '.join([ str(x) for x in sattumised ]) + '\n')
