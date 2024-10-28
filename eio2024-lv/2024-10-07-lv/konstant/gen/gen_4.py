import sys
import random
import gmpy2
inp = open(sys.argv[1], 'w')
out = open(sys.argv[2], 'w')
N = int(sys.argv[3])
mode = sys.argv[4]
random.seed(f"const4,{N},{mode}")

to_test = []
if mode.startswith("special"):
    to_test += [1, 2, 3, 4, 5, 6, 7, 8]
    to_test += [49]
    for x in range(10, 100):
        if gmpy2.is_prime(x):
            to_test += [x]
    # some actual pseudoprimes
    to_test += [29341, 1105, 561, 41041]
    if mode == "specialbig":
        to_test += [25326001, 3215031751]
        # break incomplete trial divisions
        for x in [65447, 65449, 65479, 65497, 65519, 65521]:
            to_test += [x*x]
    while len(to_test) < N:
        to_test.append(random.randrange(1, 1000000))
elif mode == "medium" or mode == "big":
    randprimes = []
    randcomps = []
    upper_bound = 2**32 if mode == "big" else 10**6
    while len(randprimes) < N//2:
        p = random.randrange(1, upper_bound)
        if gmpy2.is_prime(p): randprimes.append(p)
    while len(randcomps) < N//2:
        p = random.randrange(1, upper_bound)
        if not gmpy2.is_prime(p): randcomps.append(p)
    to_test += randprimes
    to_test += randcomps

random.shuffle(to_test)
print(4, len(to_test), file=inp)
for x in to_test:
    print(x, file=inp)
    print(int(gmpy2.is_prime(x)), file=out)
