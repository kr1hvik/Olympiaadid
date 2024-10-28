#include "testlib.h"
#include "gen_util.h"

#include <fstream>

using namespace std;

int main (int argc, char **argv) {
  registerGen(argc, argv, 1);

  string src = opt<string>("src");
  double cp = opt<double>("cp");

  ifstream fin (src.c_str());
  int n, m;
  fin >> n >> m;

  Test T;
  fin >> T.sx >> T.sy;
  T.sx--; T.sy--;

  T.grid = vector<vector<int>> (n, vector<int> (m, 0));
  for (int i = 0; i < n; i++) {
    string line;
    fin >> line;

    assert((int) line.size() == m);
    for (int j = 0; j < m; j++) {
      T.grid[i][j] = line[j] == '#';
    }
  }

  int K;
  fin >> K;

  T.portal_perm = vector<int> (K);
  for (int i = 0; i < K; i++) {
    fin >> T.portal_perm[i];
    T.portal_perm[i]--;
  }

  T.portals = vector<Portal> (K);
  for (int i = 0; i < K; i++) {
    fin >> T.portals[i].x >> T.portals[i].y;
    T.portals[i].x--;
    T.portals[i].y--;
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (T.grid[i][j])
        continue;

      bool is_portal = false;
      for (auto p : T.portals)
        if (i == p.x && j == p.y)
          is_portal = true;

      if (is_portal || rnd.next(1.0) < cp)
        T.coins.push_back(Coin {.x = i, .y = j, .w = rnd.next(1, 1'000'000'000)});
    }
  }

  permute_test(T);
  cout << T;
}
