#ifndef _GEN_GRID
#define _GEN_GRID

#include "testlib.h"
#include "gen_util.h"

#include <iostream>
#include <algorithm>
#include <utility>

// in almost any generator, the grid itself is actually kinda irrelevant.
// what matters are the connected components, and generators want to specify that instead.

struct AbstractPortal {
  int index; // 0-indexed
  std::optional<int> coin_value;
};

struct AbstractGroup {
  std::vector<AbstractPortal> portals;
  std::vector<int> extra_coins;
  int free_space = 0;
  bool start = false;
};

struct AbstractTest {
  std::vector<AbstractGroup> groups;
  std::vector<int> portal_perm;
};

Test generate_grid_bfs (AbstractTest test, int n, int m) {
  auto group_size = [](const AbstractGroup &grp) {
    return grp.portals.size() + grp.extra_coins.size() + grp.start + grp.free_space;
  };

  /*
  sort(test.groups.begin(), test.groups.end(),
    [&](const AbstractGroup &p, const AbstractGroup &q) {
      return group_size(p) > group_size(q);
    });
  */

  const int dx [4] = {1, 0, -1, 0};
  const int dy [4] = {0, 1, 0, -1};

  std::vector<std::vector<int>> grid (n, std::vector<int> (m, 1));
  auto count_free_nbors = [&](int x, int y) {
    int cnt = 0;
    for (int k = 0; k < 4; k++) {
      int nx = x + dx[k];
      int ny = y + dy[k];
      if (nx < 0 || nx >= n || ny < 0 || ny >= m)
        continue;
      if (grid[nx][ny] == 0)
        cnt++;
    }
    
    return cnt;
  };

  Test T;
  T.portal_perm = test.portal_perm;
  T.portals = std::vector<Portal> (test.portal_perm.size());
  auto assign_group = [&](const AbstractGroup &group, std::vector<std::pair<int, int>> comp) {
    shuffle(comp.begin(), comp.end());
    for (const auto &portal : group.portals) {
      auto square = comp.back();
      comp.pop_back();
      
      T.portals[portal.index] = Portal {.x = square.first, .y = square.second};
      if (portal.coin_value) {
        T.coins.push_back(Coin {.x = square.first, .y = square.second, .w = *portal.coin_value});
      }
    }
    
    for (int coin : group.extra_coins) {
      auto square = comp.back();
      comp.pop_back();
      
      T.coins.push_back(Coin {.x = square.first, .y = square.second, .w = coin});
    }
    
    if (group.start) {
      auto square = comp.back();
      comp.pop_back();
      
      T.sx = square.first;
      T.sy = square.second;
    }
  };
  
  int grp_ptr = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (grp_ptr == (int) test.groups.size())
        goto done;
      
      if (grid[i][j] == 0 || count_free_nbors(i, j) > 0)
        continue;

      std::vector<std::pair<int, int>> Q;
      std::vector<std::pair<int, int>> comp;
      grid[i][j] = 0;
      Q.emplace_back(i, j);
      comp.emplace_back(i, j);

      while (!Q.empty() && comp.size() < group_size(test.groups[grp_ptr])) {
        int p = rnd.next(Q.size());
        std::swap(Q[p], Q[(int) Q.size() - 1]);
        auto cur = Q.back();
        Q.pop_back();

        for (int k = 0; k < 4; k++) {
          int nx = cur.first + dx[k];
          int ny = cur.second + dy[k];
          if (nx < 0 || nx >= n || ny < 0 || ny >= m)
            continue;

          if (grid[nx][ny] == 1 && count_free_nbors(nx, ny) == 1) {
            grid[nx][ny] = 0;
            Q.emplace_back(nx, ny);
            comp.emplace_back(nx, ny);
          }
        }
      }

      if (comp.size() >= group_size(test.groups[grp_ptr])) {
        assign_group(test.groups[grp_ptr], comp);
        grp_ptr++;
      } else if (comp.size() >= group_size(test.groups.back())) {
        assign_group(test.groups.back(), comp);
        test.groups.pop_back();
      }
    }
  }

 done:
  assert(grp_ptr == (int) test.groups.size());

  T.grid = grid;
  return T;
}

Test generate_grid_stripy (AbstractTest test) {
  size_t m = 1;
  for (const auto &group : test.groups) 
    m = std::max(m, group.portals.size() + group.extra_coins.size() + group.free_space);

  Test T;
  T.grid = std::vector<std::vector<int>> (0);
  T.portal_perm = test.portal_perm;
  T.portals = std::vector<Portal> (test.portal_perm.size());
  T.coins = std::vector<Coin> (0);
  
  bool first = true;
  for (const auto &group : test.groups) {
    if (!first)
      T.grid.emplace_back(m, 1);
    first = false;

    T.grid.emplace_back(m, 0);
    int row = (int) T.grid.size() - 1;
    
    if (group.start) {
      T.sx = row;
      T.sy = rnd.next(m);
    }
    
    std::vector<int> order (m);
    std::iota(order.begin(), order.end(), 0);
    shuffle(order.begin(), order.end());

    for (auto portal : group.portals) {
      int col = order.back();
      order.pop_back();

      T.portals[portal.index] = Portal {.x = row, .y = col};
      if (portal.coin_value)
        T.coins.push_back(Coin {.x = row, .y = col, .w = *portal.coin_value});
    }

    for (auto val : group.extra_coins) {
      int col = order.back();
      order.pop_back();

      T.coins.push_back(Coin {.x = row, .y = col, .w = val});
    }
  }

  return T;
}

Test generate_grid_horizontal (AbstractTest test) {
  Test T;
  T.grid = std::vector<std::vector<int>> (1, std::vector<int> (0));
  T.portal_perm = test.portal_perm;
  T.portals = std::vector<Portal> (test.portal_perm.size());
  T.coins = std::vector<Coin> (0);

  bool first = true;
  for (const auto &group : test.groups) {
    if (!first)
      T.grid[0].push_back(1);
    first = false;

    int cnt = group.portals.size() + group.extra_coins.size() + group.free_space;
    if (cnt == 0)
      cnt++;

    std::vector<int> order (cnt);
    std::iota(order.begin(), order.end(), (int) T.grid[0].size());
    shuffle(order.begin(), order.end());

    if (group.start) {
      T.sx = 0;
      T.sy = order[rnd.next(cnt)];
    }

    for (auto portal : group.portals) {
      int col = order.back();
      order.pop_back();

      T.portals[portal.index] = Portal {.x = 0, .y = col };
      if (portal.coin_value) {
        T.coins.push_back(Coin {.x = 0, .y = col, .w = *portal.coin_value});
      }
    }

    for (auto val : group.extra_coins) {
      int col = order.back();
      order.pop_back();

      T.coins.push_back(Coin {.x = 0, .y = col, .w = val});
    }
    
    std::vector<int> zeros (cnt, 0);
    T.grid[0].insert(T.grid[0].end(), zeros.begin(), zeros.end());
  }

  return T;
}

#endif
