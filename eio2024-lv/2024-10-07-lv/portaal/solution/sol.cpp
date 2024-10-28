// full solution

#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

int gcd (int p, int q) {
  if (q == 0) return p;
  return gcd(q, p % q);
}

struct Edge {
  int from, to, w;
};

struct Graph {
  int n;
  vector<vector<pair<int, int>>> adj; // <to, weight> 
  vector<Edge> edges;

  vector<int> potential;
  vector<int> reachable;
  
  Graph (int _n) : n(_n), adj(_n, vector<pair<int, int>> (0)) { }

  void add_edge (int from, int to, int w) {
    adj[from].emplace_back(to, w);
    edges.push_back(Edge {.from = from, .to = to, .w = w});
  }

  void dfs (int u, int p) {
    potential[u] = p;
    reachable[u] = 1;

    for (auto e : adj[u]) {
      if (reachable[e.first])
        continue;

      dfs(e.first, p + e.second);
    }
  }
  
  void run (int start) {
    potential = vector<int> (n, 0);
    reachable = vector<int> (n, 0);
    
    dfs(start, 0);

    int gc = 0;
    for (auto e : edges) {
      if (!reachable[e.from])
        continue;

      gc = gcd(gc, abs(potential[e.from] - potential[e.to] + e.w));
    }

    if (gc == 0) // no portal is reachable from the start at all, avoid division by 0
      return;
    
    for (int i = 0; i < n; i++) {
      potential[i] %= gc;
      if (potential[i] < 0)
        potential[i] += gc;
    }

    cerr << " " << gc << '\n';
  }
};

const int dx [4] = {1, 0, -1, 0};
const int dy [4] = {0, 1, 0, -1};

void solve () {
  int n, m;
  cin >> n >> m;

  int sx, sy;
  cin >> sx >> sy;

  vector<vector<char>> grid (n + 2, vector<char> (m + 2, '#'));
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      cin >> grid[i][j];

  int coinc;
  cin >> coinc;

  vector<vector<ll>> coin_val (n + 2, vector<ll> (m + 2, 0));
  for (int i = 0; i < coinc; i++) {
    int x, y, w;
    cin >> x >> y >> w;

    coin_val[x][y] = w;
  }

  int K;
  cin >> K;

  vector<int> portal_perm (K);
  for (int i = 0; i < K; i++) {
    cin >> portal_perm[i];
    portal_perm[i]--;
  }

  vector<pair<int, int>> portal_pos (K);
  vector<vector<int>> portal_id (n + 2, vector<int> (m + 2, -1));
  for (int i = 0; i < K; i++) {
    cin >> portal_pos[i].first >> portal_pos[i].second;
    portal_id[portal_pos[i].first][portal_pos[i].second] = i;
  }

  Graph G ((n + 2) * (m + 2));
  auto idx = [&](int i, int j) { return (m + 2) * i + j; };
  auto idxp = [&](pair<int, int> pr) { return idx(pr.first, pr.second); };

  for (int x = 1; x <= n; x++) {
    for (int y = 1; y <= m; y++) {
      if (grid[x][y] == '#')
        continue;

      for (int k = 0; k < 4; k++) {
        int nx = x + dx[k], ny = y + dy[k];
        if (grid[nx][ny] == '#')
          continue;

        G.add_edge(idx(x, y), idx(nx, ny), 0);
      }
    }
  }

  for (int i = 0; i < K; i++) {
    G.add_edge(idxp(portal_pos[i]), idxp(portal_pos[portal_perm[i]]), 1);
    G.add_edge(idxp(portal_pos[portal_perm[i]]), idxp(portal_pos[i]), -1);
  }

  G.run(idx(sx, sy));

  ll ans = 0;
  for (int x = 1; x <= n; x++) {
    for (int y = 1; y <= m; y++) {
      if (portal_id[x][y] == -1 && G.reachable[idx(x, y)])
        ans += coin_val[x][y];

      if (portal_id[x][y] != -1 && G.reachable[idx(x, y)] && G.potential[idx(x, y)] == 0)
        ans += coin_val[x][y];
    }
  }

  cout << ans << '\n';
}

int main () {
  ios::sync_with_stdio(false);
  cin.tie(0);

  solve();
}
