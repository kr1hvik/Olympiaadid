import sys
import random
import solver
from string import ascii_lowercase
import time

X = 823102663

generate_tests = range(100)

def make_test(ti, test):
    if ti not in generate_tests:
        return
    with open(f"../input/input{ti}.txt", "w") as f:
        print(len(test), file=f)
        for n, s in test:
            print(n, file=f)
            print(s, file=f)
    t0 = time.time()
    with open(f"../output/output{ti}.txt", "w") as f:
        for n, s in test:
            rs = solver.solve(s, n)
            rs.sort()
            print(len(rs), file=f)
            print(" ".join(rs), file=f)
    print(ti, f"{time.time() - t0:.3f}")
            
def merge(a, b):
    ai = 0
    bi = 0
    r = ""
    while ai < len(a) and bi < len(b):
        if random.random() < 0.5:
            c = a[ai]
            ai += 1
        else:
            c = b[bi]
            bi += 1
        r += c
    r += a[ai:]
    r += b[bi:]
    return r

def merge_n(s, n):
    r = ""
    for _ in range(n):
        r = merge(r, s)
    return r

def abc(n, l, v):
    chs = random.sample(ascii_lowercase, v)
    s = "".join(random.choice(chs) for _ in range(l))

    return merge_n(s, n)


def abab(n, l):
    a, b = random.sample(ascii_lowercase, 2)
    s = "".join(a + b for _ in range(l))[:l]

    return merge_n(s, n)


def misc_2(l):
    test = []
    for u in (2, 3, 5, 8, l):
        test.append((2, abc(2, u, 1)))
        s = "".join(random.sample(ascii_lowercase, u))
        test.append((2, merge_n(s, 2)))
        test.append((2, abc(2, u, 4)))
    test.append((2, abc(2, 1, 1)))
    return test

if len(sys.argv) >= 2:
    generate_tests = list(map(int, sys.argv[1:]))

ti = 1

# Small: 3
sc = ti
l = 11

random.seed(X)
make_test(ti, [(2, abc(2, l, 2)) for _ in range(20)])
ti += 1

random.seed(X+1)
make_test(ti, misc_2(l))
ti += 1

random.seed(X+2)
make_test(ti, [(2, abab(2, l)) for _ in range(20)])
ti += 1

assert ti - sc == 3

# Two: 3
sc = ti
l = 24

random.seed(X + 21)
make_test(ti, misc_2(l))
ti += 1

random.seed(X + 22)
make_test(ti, [(2, abc(2, l, 2)) for _ in range(20)])
ti += 1

random.seed(X + 23)
make_test(ti, [(2, abab(2, l)) for _ in range(20)])
ti += 1

assert ti - sc == 3


# Max: 6
sc = ti

random.seed(X + 30)
make_test(ti, misc_2(24))
ti += 1

random.seed(X + 31)
make_test(ti, [(10, abab(10, 7)) for _ in range(20)])
ti += 1

random.seed(X + 32)
make_test(ti, [(8, abab(8, 8)) for _ in range(20)])
ti += 1

random.seed(X + 34)
make_test(ti, [(5, abc(5, 10, 4)) for _ in range(20)])
ti += 1

random.seed(X + 35)
make_test(ti, [(3, abab(3, 15)) for _ in range(20)])
ti += 1

random.seed(X + 36)
make_test(ti, [(2, abab(2, 24)) for _ in range(20)])
ti += 1

assert ti - sc == 6    
