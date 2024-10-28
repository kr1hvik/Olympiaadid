import sys
import random
inp = open(sys.argv[1], 'w')
out = open(sys.argv[2], 'w')
ntests = int(sys.argv[3])
N = int(sys.argv[4])
random.seed(f"const0,{ntests},{N}")
print(0, ntests, file=inp)
for _ in range(ntests):
    i = random.randrange(N)
    print(N, i, file=inp)
    arr = [random.randrange(2**32) for _ in range(N)]
    print(*arr, file=inp)
    print(arr[i], file=out)
