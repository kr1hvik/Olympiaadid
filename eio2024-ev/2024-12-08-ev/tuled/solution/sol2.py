x, y, n = map(int, (input() for _ in range(3)))

# Eurod -> sendid
n *= 100

# Maksimaalne käigushoitav tundide arv
hx = 18 - 14
hy = 23 - 18

# Võtame x soodsamaks ajaks
if y < x:
    # Vahetame
    x, y = y, x
    hx, hy = hy, hx

# x <= y, võtame selle enne
t = 0
if hx * x > n:
    # Saame ainult osa võtta
    t = n / x
else:
    # Võtame kogu x
    t = hx
    n -= hx * x
    
    # Võtame y ka
    t += min(hy, n / y)

print(t)