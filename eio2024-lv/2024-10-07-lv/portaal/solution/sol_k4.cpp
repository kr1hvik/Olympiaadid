#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define x first
#define y second

struct State {
  int x, y, t;
};

struct Coin {
  int x, y, val;
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

void solve () {
  int n, m;
  cin >> n >> m;

  int sx, sy;
  cin >> sx >> sy;

  vector<vector<int>> grid (n + 2, vector<int> (m + 2, 1));
  for (int i = 1; i <= n; i++) {
    string line;
    cin >> line;
    for (int j = 1; j <= m; j++)
      if (line[j - 1] == '.')
        grid[i][j] = 0;
  }

  int coinc;
  cin >> coinc;
  
  vector<Coin> coins (coinc);
  for (int i = 0; i < coinc; i++)
    cin >> coins[i].x >> coins[i].y >> coins[i].val;

  int K;
  cin >> K;

  vector<int> perm (K + 1);
  for (int i = 1; i <= K; i++)
    cin >> perm[i];

  vector<pair<int, int>> portals (K + 1);
  vector<vector<int>> portal_pos (n + 2, vector<int> (m + 2, 0));
  for (int i = 1; i <= K; i++) {
    cin >> portals[i].x >> portals[i].y;
    portal_pos[portals[i].x][portals[i].y] = i;
  }

  int kcycle = factlcm(K);
  vector<vector<vector<int>>> reachable
    (n + 2, vector<vector<int>> (m + 2, vector<int> (kcycle, 0)));
  reachable[sx][sy][0] = 1;
  queue<State> Q;
  Q.push(State {.x = sx, .y = sy, .t = 0});

  while (!Q.empty()) {
    auto cur = Q.front();
    Q.pop();

    for (int k = 0; k < 4; k++) {
      int nx = cur.x + dx[k];
      int ny = cur.y + dy[k];

      if (grid[nx][ny])
        continue;

      if (reachable[nx][ny][cur.t])
        continue;

      reachable[nx][ny][cur.t] = 1;
      Q.push(State {.x = nx, .y = ny, .t = cur.t});
    }

    if (portal_pos[cur.x][cur.y] != 0) {
      int p = portal_pos[cur.x][cur.y];
      auto po = portals[perm[p]];
      if (!reachable[po.x][po.y][(cur.t + 1) % kcycle]) {
        reachable[po.x][po.y][(cur.t + 1) % kcycle] = 1;
        Q.push(State {.x = po.x, .y = po.y, .t = (cur.t + 1) % kcycle});
      }
    }
  }

  long long ans = 0;
  for (auto coin : coins) {
    bool ok = false;
    if (portal_pos[coin.x][coin.y]) {
      int x = coin.x;
      int y = coin.y;
      for (int k = 0; k < kcycle; k++) {
        if (reachable[x][y][k])
          ok = true;

        auto po = portals[perm[portal_pos[x][y]]];
        x = po.x;
        y = po.y;
      }
    } else {
      for (int k = 0; k < kcycle; k++)
        if (reachable[coin.x][coin.y][k])
          ok = true;
    }

    if (ok)
      ans += coin.val;
  }

  cout << ans << '\n';
}

int main () {
  ios::sync_with_stdio(false);
  cin.tie(0);

  solve();
}
