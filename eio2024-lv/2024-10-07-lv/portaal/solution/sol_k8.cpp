// like sol_k4.cpp, but compresses the connected components of the grid into one
// so that we have only k vertices in the graph and can get away with O(k k!)

#include <iostream>
#include <vector>

using namespace std;

#define x first
#define y second

struct Coin {
  int x, y, w;
};

int gcd (int p, int q) {
  if (q == 0) return p;
  return gcd(q, p % q);
}

int lcm (int p, int q) {
  p /= gcd(p, q);
  return p * q;
}

int factlcm (int x) {
  int ans = 1;
  for (int i = 1; i <= x; i++)
    ans = lcm(ans, i);
  return ans;
}

const int dx [4] = {1, 0, -1, 0};
const int dy [4] = {0, 1, 0, -1};

void mark_components (int x, int y, int comp_id,
                      const vector<vector<int>> &grid,
                      vector<vector<int>> &component) {
  component[x][y] = comp_id;

  for (int k = 0; k < 4; k++) {
    int nx = x + dx[k];
    int ny = y + dy[k];

    if (grid[nx][ny])
      continue;
    
    if (component[nx][ny] == -1)
      mark_components(nx, ny, comp_id, grid, component);
  }
}

void mark_reachable (int u, int t, int kcycle,
                     const vector<vector<pair<int, int>>> &adj,
                     vector<vector<int>> &reachable) {
  reachable[u][t] = 1;

  for (auto e : adj[u]) {
    int v = e.first, nt = (t + e.second) % kcycle;
    if (reachable[v][nt])
      continue;

    mark_reachable(v, nt, kcycle, adj, reachable);
  }
}

void solve () {
  int n, m;
  cin >> n >> m;

  int sx, sy;
  cin >> sx >> sy;

  vector<vector<int>> grid (n + 2, vector<int> (m + 2, 1));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      char c;
      cin >> c;
      
      if (c == '.')
        grid[i][j] = 0;
    }
  }

  int coinc;
  cin >> coinc;

  vector<Coin> coins (coinc);
  for (int i = 0; i < coinc; i++)
    cin >> coins[i].x >> coins[i].y >> coins[i].w;

  int K;
  cin >> K;

  vector<int> portal_perm (K);
  for (int i = 0; i < K; i++) {
    cin >> portal_perm[i];
    portal_perm[i]--;
  }

  vector<pair<int, int>> portals (K);
  for (int i = 0; i < K; i++)
    cin >> portals[i].x >> portals[i].y;

  vector<vector<int>> components (n + 2, vector<int> (m + 2, -1));
  int vc = K;
  for (auto portal : portals) {
    if (components[portal.x][portal.y] == -1) {
      mark_components(portal.x, portal.y, vc, grid, components);
      vc++;
    }
  }

  if (components[sx][sy] == -1) {
    mark_components(sx, sy, vc, grid, components);
    vc++;
  }

  vector<vector<pair<int, int>>> adj (vc, vector<pair<int, int>> (0));
  for (int i = 0; i < K; i++) {
    adj[i].emplace_back(portal_perm[i], 1);
  }

  for (int i = 0; i < K; i++) {
    int p = components[portals[i].x][portals[i].y];
    adj[i].emplace_back(p, 0);
    adj[p].emplace_back(i, 0);
  }

  int kcycle = factlcm(K);
  vector<vector<int>> reachable (vc, vector<int> (kcycle, 0));
  int start = components[sx][sy];
  mark_reachable(start, 0, kcycle, adj, reachable);

  long long ans = 0;
  for (auto coin : coins) {
    int p = -1;
    for (int i = 0; i < K; i++)
      if (make_pair(coin.x, coin.y) == portals[i])
        p = i;

    bool ok = false;
    if (p == -1) {
      // just check if the square is reachable at all...
      p = components[coin.x][coin.y];
      if (p == -1)
        continue;
      
      for (int i = 0; i < kcycle; i++)
        if (reachable[p][i])
          ok = true;
    } else {
      // reachable[p][0] or reachable[A[p]][1] or reachable[A[A[p]]][2]...
      for (int i = 0; i < kcycle; i++) {
        if (reachable[p][i])
          ok = true;

        p = portal_perm[p];
      }
    }

    if (ok)
      ans += coin.w;
  }

  cout << ans << '\n';
}

int main () {
  ios::sync_with_stdio(false);
  cin.tie(0);

  solve();
}
