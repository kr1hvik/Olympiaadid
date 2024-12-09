from collections import Counter

n = int(input())

loe = Counter(input() for _ in range(n))

if n % 2 == 1:
    print(-1)
else:
    v = sum(c % 2 for c in loe.values())
    print(v // 2)

