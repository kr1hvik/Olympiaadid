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

lo = 1
hi = 101
while hi - lo > 1:
    m = (lo + hi) // 2
    if len(proovi(m)) > 0:
        lo = m
    else:
        hi = m

print(sorted(proovi(lo))[0])
