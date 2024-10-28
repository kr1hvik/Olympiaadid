#include "testlib.h"
#include <vector>
#include <set>

using namespace std;

const int MAX_NM = 100'000;
const int MAX_C = 100'000;
const int MAX_W = 1'000'000'000;
const int MAX_K = 100'000;

int main (int argc, char **argv) {
  registerValidation(argc, argv);

  int n = inf.readInt(1, MAX_NM, "N");
  inf.readSpace();
  int m = inf.readInt(1, MAX_NM, "M");
  inf.readEoln();

  ensuref((long long) n * (long long) m <= MAX_NM, "nm exceeds limit");

  int sx = inf.readInt(1, n, "X") - 1;
  inf.readSpace();
  int sy = inf.readInt(1, m, "Y") - 1;
  inf.readEoln();

  vector<string> grid (n);
  for (int i = 0; i < n; i++) {
    grid[i] = inf.readWord();
    ensuref((int) grid[i].size() == m, "line too wide");
    for (char c : grid[i]) {
      ensuref(c == '.' || c == '#', "illegal symbol in line");
    }
    inf.readEoln();
  }

  ensuref(grid[sx][sy] == '.', "start position on blocked square");

  // coins
  int C = inf.readInt(1, MAX_C, "C");
  inf.readEoln();

  set<pair<int, int>> coin_pos;
  for (int i = 0; i < C; i++) {
    int x = inf.readInt(1, n, "Xi") - 1;
    inf.readSpace();
    int y = inf.readInt(1, m, "Yi") - 1;
    inf.readSpace();
    inf.readInt(1, MAX_W, "W");
    inf.readEoln();

    ensuref(grid[x][y] == '.', "coin on blocked square");
    ensuref(!coin_pos.count(make_pair(x, y)), "coin in repeated location");
    coin_pos.emplace(x, y);
  }

  // portals
  int K = inf.readInt(1, MAX_K, "K");
  inf.readEoln();

  vector<int> perm (K);
  for (int i = 0; i < K; i++) {
    perm[i] = inf.readInt(1, K, "Ai");
    if (i != K - 1)
      inf.readSpace();
  }
  inf.readEoln();

  ensuref((int) (set<int> (perm.begin(), perm.end())).size() == K, "A is not a permutation");

  set<pair<int, int>> portal_pos;
  for (int i = 0; i < K; i++) {
    int x = inf.readInt(1, n, "Ui") - 1;
    inf.readSpace();
    int y = inf.readInt(1, m, "Vi") - 1;
    inf.readEoln();

    ensuref(grid[x][y] == '.', "portal on blocked square");
    ensuref(!portal_pos.count(make_pair(x, y)), "portal in repeated location");
    portal_pos.emplace(x, y);
  }

  inf.readEof();

  if (validator.group() == "k1")
    ensure(K == 1);
  if (validator.group() == "k2") {
    ensure(K == 2);
    ensure(perm[0] == 2);
    ensure(perm[1] == 1);
  }
  if (validator.group() == "k4")
    ensure(K <= 4);
  if (validator.group() == "k8")
    ensure(K <= 8);
  if (validator.group() == "k16")
    ensure(K <= 16);
  if (validator.group() == "k1e3")
    ensure(K <= 1000);
}
