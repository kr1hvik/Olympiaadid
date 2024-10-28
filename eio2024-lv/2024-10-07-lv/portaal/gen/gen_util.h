#ifndef _GEN_UTIL
#define _GEN_UTIL

#include <vector>
#include <iostream>
#include <cassert>
#include <numeric>

struct Portal {
  int x, y; // 0-indexed
};

struct Coin {
  int x, y; // 0-indexed
  int w;
};

struct Test {
  std::vector<std::vector<int>> grid; // 0 is unblocked, 1 is blocked
  std::vector<int> portal_perm; // 0-indexed
  std::vector<Portal> portals;
  std::vector<Coin> coins;
  int sx, sy;
};

void permute_test (Test &T) {
  shuffle(T.coins.begin(), T.coins.end());

  int K = T.portals.size();
  std::vector<int> q = std::vector<int> (K);
  std::iota(q.begin(), q.end(), 0);
  shuffle(q.begin(), q.end());

  std::vector<int> iq = std::vector<int> (K);
  for (int i = 0; i < K; i++)
    iq[q[i]] = i;

  std::vector<Portal> new_portals (K);
  for (int i = 0; i < K; i++)
    new_portals[q[i]] = T.portals[i];

  std::vector<int> new_portal_perm (K);
  for (int i = 0; i < K; i++)
    new_portal_perm[i] = q[T.portal_perm[iq[i]]];

  T.portals = new_portals;
  T.portal_perm = new_portal_perm;
}

// prints the test in the correct format, including using 1-indexed values
std::ostream& operator<< (std::ostream &out, const Test &T) {
  int n = T.grid.size();
  int m = T.grid[0].size();
  out << n << " " << m << '\n';

  out << 1 + T.sx << " " << 1 + T.sy << '\n';

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (T.grid[i][j])
        out << '#';
      else
        out << '.';
    }
    out << '\n';
  }

  out << T.coins.size() << '\n';
  for (const auto& coin : T.coins) 
    out << 1 + coin.x << " " << 1 + coin.y << " " << coin.w << '\n';

  int K = T.portals.size();
  out << K << '\n';
  for (int i = 0; i < K; i++) {
    out << 1 + T.portal_perm[i];
    if (i != K - 1)
      out << " ";
  }
  out << '\n';

  for (const auto& portal : T.portals)
    out << 1 + portal.x << " " << 1 + portal.y << '\n';

  return out;
}

#endif
