// Simple generator
// Generates a random grid by generating a random forest, then applying random noise
// Places the coins and portals in random locations

#include "testlib.h"
#include "gen_util.h"

using namespace std;

class DSU {
  vector<int> root, rnk;

public:
  DSU (int _vertexc) {
    root = vector<int> (_vertexc);
    rnk = vector<int> (_vertexc, 0);
    for (int i = 0; i < _vertexc; i++) {
      root[i] = i;
    }
  }

  int find (int u) {
    if (u != root[u]) {
      root[u] = find(root[u]);
    }
    return root[u];
  }

  void merge (int u, int v) {
    u = find(u);
    v = find(v);

    if (u == v) {
      return;
    }

    if (rnk[u] < rnk[v]) {
      swap(u, v);
    }

    root[v] = u;

    if (rnk[u] == rnk[v]) {
      rnk[u]++;
    }
  }
};

vector<vector<int>> make_tree (int n, int m, int comps) {
  vector<vector<int>> grid (n, vector<int> (m, 1));
  vector<vector<int>> id (n, vector<int> (m, -1));

  int free_id = 0;
  for (int i = 0; i < n; i += 2) {
    for (int j = 0; j < m; j += 2) {
      grid[i][j] = 0;
      id[i][j] = free_id;
      free_id++;
    }
  }

  struct Edge {
    int u_id, v_id;
    int x, y;
  };

  vector<Edge> edges;
  for (int i = 0; i < n; i += 2) {
    for (int j = 0; j < m; j += 2) {
      if (i + 2 < n)
        edges.push_back(Edge {.u_id = id[i][j], .v_id = id[i + 2][j], .x = i + 1, .y = j});
      if (j + 2 < m)
        edges.push_back(Edge {.u_id = id[i][j], .v_id = id[i][j + 2], .x = i, .y = j + 1});
    }
  }

  shuffle(edges.begin(), edges.end());

  DSU dsu (free_id);
  int cur_comps = free_id;
  for (auto e : edges) {
    if (cur_comps <= comps)
      break;

    int u = dsu.find(e.u_id);
    int v = dsu.find(e.v_id);
    if (u == v)
      continue;

    dsu.merge(u, v);
    grid[e.x][e.y] = 0;
    cur_comps--;
  }

  return grid;
}

int main (int argc, char **argv) {
  registerGen(argc, argv, 1);

  int n = opt<int>("n");
  int m = opt<int>("m");
  int c = opt<int>("c");
  int k = opt<int>("k");
  double noise = opt<double>("noise");
  int comps = opt<int>("comps");

  Test t;
  t.grid = make_tree(n, m, comps);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      if (rnd.next(1.0) < noise)
        t.grid[i][j] ^= 1;

  do {
    t.sx = rnd.next(n);
    t.sy = rnd.next(m);
  } while (t.grid[t.sx][t.sy]);

  set<pair<int, int>> seen_coins;
  for (int i = 0; i < c; i++) {
    Coin coin;
    do {
      coin.x = rnd.next(n);
      coin.y = rnd.next(m);
    } while (t.grid[coin.x][coin.y] || seen_coins.count(make_pair(coin.x, coin.y)));
    coin.w = rnd.next(1, 1'000'000'000);

    t.coins.push_back(coin);
    seen_coins.emplace(coin.x, coin.y);
  }

  // TODO: portals...
  
  set<pair<int, int>> seen_portals;
  for (int i = 0; i < k; i++) {
    Portal p;
  }
  
  cout << t;
}
