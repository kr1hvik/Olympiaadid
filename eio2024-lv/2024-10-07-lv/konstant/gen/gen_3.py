import sys
import random
inp = open(sys.argv[1], 'w')
out = open(sys.argv[2], 'w')
n_tests = int(sys.argv[3])
N = int(sys.argv[4])
random.seed(f"const3,{n_tests},{N}")

#dijkstra mis kontrollib lühima tee ühesust
def dijkstra(g, start, end):
    dist = {x: float('inf') for x in g.keys()}
    dist[start] = 0
    prev = {}
    q = set(g.keys())
    while len(q) > 0:
        u = min(q, key=lambda x: dist.get(x, float('inf')))
        q.remove(u)
        if u == end: break
        for (v, cost) in g[u]:
            alt = dist[u] + cost
            if alt < dist[v]:
                prev[v] = [u]
                dist[v] = alt
            elif alt == dist[v]:
                prev[v].append(u)
    if dist[end] == float('inf'): return None, None
    t = end
    path = [t]
    while t != start:
        prevs = prev[t]
        if len(prevs) > 1: return None, None
        t = prevs[0]
        path.append(t)
    return dist[end], path[::-1]

def print_inp(A, start, end):
    global testsreal
    testsreal += 1
    print(N, start, end, file=inp)
    for row in A:
        print(' '.join(map(str, row)), file=inp)

testsreal = 0
max_weight = 2**32 // N
print(3, n_tests, file=inp)
for TESTNR in range(n_tests - 5):
    # random dense graph
    while 1:
        adj_mat = [[random.randrange(1, max_weight) for _ in range(N)] for _ in range(N)]
        for i in range(N): adj_mat[i][i] = 0
        g = {i: [(j, c) for j, c in enumerate(adj_mat[i]) if j != i] for i in range(N)}
        start, end = random.sample(range(N), k=2)
        if TESTNR == 0: start = end
        cost, path = dijkstra(g, start, end)
        if path is not None:
            print_inp(adj_mat, start, end)
            print(cost, file=out)
            print(len(path), file=out)
            print(' '.join(map(str, path)), file=out)
            break

for _ in range(3):
    # ahel
    chain_ord = list(range(N))
    random.shuffle(chain_ord)
    start = chain_ord[0]
    end = chain_ord[-1]
    adj_mat = [[0]*N for _ in range(N)]
    cost = 0
    for i, j in zip(chain_ord, chain_ord[1:]):
        adj_mat[i][j] = random.randrange(max_weight//2, max_weight)
        cost += adj_mat[i][j]
    print_inp(adj_mat, start, end)
    print(cost, file=out)
    print(N, file=out)
    print(' '.join(map(str, chain_ord)), file=out)

# ahel aga igast muud teed on ka
chain_ord = list(range(N))
random.shuffle(chain_ord)
start = chain_ord[0]
end = chain_ord[-1]
adj_mat = [[random.randrange(max_weight*7//8, max_weight) for _ in range(N)] for _ in range(N)]
for i in range(N): adj_mat[i][i] = 0
cost = 0
for i, j in zip(chain_ord, chain_ord[1:]):
    adj_mat[i][j] = random.randrange(1, max_weight//(2*N))
    cost += adj_mat[i][j]
print_inp(adj_mat, start, end)
print(cost, file=out)
print(N, file=out)
print(' '.join(map(str, chain_ord)), file=out)

# kahendpuu ühest lehest teise
list_ord = list(range(N))
random.shuffle(list_ord)
layers = []
ci = 0
l = 1
done = False
while not done:
    layer = []
    for _ in range(l):
        layer.append(list_ord[ci])
        ci += 1
        if ci == N:
            done = True
            break
    layers.append(layer)
    l *= 2
rand = lambda: random.randrange(max_weight*7//8, max_weight)
adj_mat = [[0 for _ in range(N)] for _ in range(N)]
for l1, l2 in zip(layers, layers[1:]):
    for i, x in enumerate(l1):
        if i * 2 >= len(l2):
            break
        y1 = l2[i*2]
        adj_mat[x][y1] = rand()
        adj_mat[y1][x] = rand()

        if i * 2 + 1 >= len(l2):
            break
        y2 = l2[i*2 + 1]
        adj_mat[x][y2] = rand()
        adj_mat[y2][x] = rand()
start, end = layers[-1][0], layers[-1][-1]
g = {i: [(j, c) for j, c in enumerate(adj_mat[i]) if j != i and c != 0] for i in range(N)}
cost, path = dijkstra(g, start, end)
print_inp(adj_mat, start, end)
print(cost, file=out)
print(len(path), file=out)
print(' '.join(map(str, path)), file=out)
assert n_tests == testsreal
