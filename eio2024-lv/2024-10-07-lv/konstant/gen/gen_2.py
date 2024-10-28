import sys
import random
inp = open(sys.argv[1], 'w')
out = open(sys.argv[2], 'w')
N = int(sys.argv[3])
mode = sys.argv[4]
random.seed(f"const2,{N},{mode}")

print("2 10", file=inp)
n_random = 10
maxcomps = 10
if mode == 'a':
    n_random = 8
    maxcomps = N//2
    print(N, file=inp)
    for _ in range(N):
        print(' '.join('0'*N), file=inp)
    print(N, file=out)
    
    print(N, file=inp)
    for i in range(N):
        print(' '.join(['0' if j == i else '1' for j in range(N)]), file=inp)
    print(1, file=out)

# join up random components until there are few enough left
# then add some amount of redundant edges
for _ in range(n_random):
    target_components = random.randrange(1, maxcomps)
    edges = set()
    components = {x: [x] for x in range(N)}
    while len(components) > target_components:
        c1, c2 = random.sample(list(components.keys()), k=2)
        node1 = random.choice(components[c1])
        node2 = random.choice(components[c2])
        node1, node2 = sorted((node1, node2))
        edges.add((node1, node2))
        components[c2] += components[c1]
        del components[c1]
    for c in components.values():
        # try to add len(c) / 2 random edges
        # (some will fail because they already exist)
        for _ in range(len(c)//2):
            n1, n2 = random.sample(c, 2)
            n1, n2 = sorted((n1, n2))
            edges.add((n1, n2))
    A = [['0']*N for _ in range(N)]
    for (n1,n2) in edges:
        A[n1][n2] = '1'
        A[n2][n1] = '1'
    print(N, file=inp)
    for row in A:
        print(' '.join(row), file=inp)
    print(target_components, file=out)
