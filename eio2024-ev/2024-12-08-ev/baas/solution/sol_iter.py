n, m = map(int, input().split())

read = [input().split() for _ in range(m)]

def proovi(l):
    # Kas pikkus sobib?
    # Kui jah, siis anna sobivad sõned ka
    sobivad = {x[:l] for x in read[0] if len(x) >= l}
    for rida in read:
        praegu = {x[:l] for x in rida if len(x) >= l}
        sobivad &= praegu
    
    return sobivad

l = 1
parim = proovi(1)
while True:
    l += 1
    hetkel = proovi(l)
    if len(hetkel) == 0:
        break
    parim = hetkel

print(sorted(parim)[0])
