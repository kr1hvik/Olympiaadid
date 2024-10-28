from itertools import combinations

t = int(input())

for _ in range(t):
    n = int(input())
    s = input()
    s = list(map(ord, s))
    l = len(s) // n
    good = set()
    s1 = s[1:]
    for ai in combinations(range(len(s) - 1), l - 1):
        ai2 = 0
        a = [s[0]]
        b = []
        for i, c in enumerate(s1):
            if ai2 < l-1 and ai[ai2] == i:
                ai2 += 1
                a.append(c)
            else:
                b.append(c)
        if a == b:
            good.add(tuple(a))
    print(len(good))
    print(" ".join("".join(map(chr, x)) for x in sorted(good)))
