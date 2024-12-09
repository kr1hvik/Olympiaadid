
m, n, x1, y1, x2, y2 = map(int, input().split())

if x1 == x2:
    x1, y1 = y1, x1
    x2, y2 = y2, x2
    m, n = n, m

if y1 == y2:
    # Telgede sihis volditud
    print(max(n - y1, y1) * m)
else:
    # Käime jõuga kõik ruudud läbi ja vaatame, mis neist saab
    ruudud = set()
    pool = 0
    if (x1 < x2) != (y1 < y2):
        x1 -= 1
        x2 -= 1
    vx, vy = x2 - x1, y2 - y1
    
    for x in range(m):
        for y in range(n):
            dx, dy = x - x1, y - y1
            v = dx * vy - dy * vx
            if v == 0:
                # Ruut on poolitusjoonel
                pool += 1
            elif v > 0:
                # Ruut on ühel pool volti
                ruudud.add((x, y))
            else:
                # Ruut on teisel pool volti
                # Peegelda (voldi) see ruut samale poolele kui teised
                if (x1 < x2) == (y1 < y2):
                    xr, yr = dy + x1, dx + y1
                else:
                    xr, yr = x1 - dy, y1 - dx
                ruudud.add((xr, yr))
    print(len(ruudud) + pool / 2)
