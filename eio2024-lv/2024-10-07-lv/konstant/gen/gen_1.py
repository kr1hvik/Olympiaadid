import sys
import random
inp = open(sys.argv[1], 'w')
out = open(sys.argv[2], 'w')
ntests = int(sys.argv[3])
N = int(sys.argv[4])
# up to N basically guarantees some collisions
upper_bound = 2**32 - 1 if sys.argv[5] == "big" else N
random.seed(f"const1,{ntests},{N},{upper_bound}")
print(1, ntests, file=inp)
for _ in range(ntests):
    arr = [random.randrange(upper_bound) for _ in range(N)]
    print(N, file=inp)
    print(' '.join(map(str, arr)), file=inp)
    arr.sort()
    print(' '.join(map(str, arr)), file=out)
