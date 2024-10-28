import sys
from types import GeneratorType

def iterative (f, stack=[]):
    def wrapped_func (*args, **kwargs):
        if stack: return f(*args, **kwargs)
        to = f(*args, **kwargs)
        while True:
            if type(to) is GeneratorType:
                stack.append(to)
                to = next(to)
                continue
            stack.pop()
            if not stack: break
            to = stack[-1].send(to)
        return to

    return wrapped_func

def gcd (p, q):
    if q == 0:
        return p;
    return gcd(q, p % q)

class Edge:
    def __init__ (self, fro, to, w):
        self.fro = fro
        self.to = to
        self.w = w

class Graph:
    def __init__ (self, n):
        self.n = n
        self.adj = [[] for _ in range(n)]
        self.edges = []

    def add_edge (self, fro, to, w):
        self.adj[fro].append((to, w))
        self.edges.append(Edge(fro, to, w))

    @iterative
    def dfs (self, u, p):
        self.potential[u] = p
        self.reachable[u] = True

        for to, w in self.adj[u]:
            if self.reachable[to]:
                continue

            yield self.dfs(to, p + w)
        yield

    def run (self, start):
        self.potential = [0 for _ in range(self.n)]
        self.reachable = [False for _ in range(self.n)]

        self.dfs(start, 0)

        gc = 0
        for e in self.edges:
            if not self.reachable[e.fro]:
                continue

            gc = gcd(gc, abs(self.potential[e.fro] - self.potential[e.to] + e.w))

        if gc == 0:
            return
            
        for i in range(self.n):
            self.potential[i] %= gc

dx = [1, 0, -1, 0]
dy = [0, 1, 0, -1]

def solve ():
    n, m = map(int, sys.stdin.readline().split())
    sx, sy = map(int, sys.stdin.readline().split())

    grid = [[True for _ in range(m + 2)] for _ in range(n + 2)]
    for i in range(1, n + 1):
        line = sys.stdin.readline()
        for j in range(1, m + 1):
            grid[i][j] = line[j - 1] == '#'

    coinc = int(sys.stdin.readline())
    coin_val = [[0 for _ in range(m + 2)] for _ in range(n + 2)]
    for i in range(coinc):
        x, y, w = map(int, sys.stdin.readline().split())
        coin_val[x][y] = w

    K = int(sys.stdin.readline())
    portal_perm = list(map(int, sys.stdin.readline().split()))
    for i in range(K):
        portal_perm[i] -= 1

    portal_pos = [(0, 0) for _ in range(K)]
    portal_id = [[-1 for _ in range(m + 2)] for _ in range(n + 2)]
    for i in range(K):
        x, y = map(int, sys.stdin.readline().split())
        portal_pos[i] = (x, y)
        portal_id[x][y] = i

    G = Graph((n + 2) * (m + 2))
    idx = lambda i, j: (m + 2) * i + j

    for x in range(1, n + 1):
        for y in range(1, m + 1):
            if grid[x][y]:
                continue

            for k in range(4):
                nx = x + dx[k]
                ny = y + dy[k]
                if grid[nx][ny]:
                    continue

                G.add_edge(idx(x, y), idx(nx, ny), 0)

    for i in range(K):
        G.add_edge(idx(*portal_pos[i]), idx(*portal_pos[portal_perm[i]]), 1)
        G.add_edge(idx(*portal_pos[portal_perm[i]]), idx(*portal_pos[i]), -1)

    G.run(idx(sx, sy))

    ans = 0
    for x in range(1, n + 1):
        for y in range(1, m + 1):
            if portal_id[x][y] == -1 and G.reachable[idx(x, y)]:
                ans += coin_val[x][y]

            if portal_id[x][y] != -1 and G.reachable[idx(x, y)] and G.potential[idx(x, y)] == 0:
                ans += coin_val[x][y]

    print(ans)

if __name__ == "__main__":
    solve()
