#include "gen_grid.h"

using namespace std;

int ceilf (int a, int b) {
  return (a + b - 1) / b;
}

template<typename T>
T opt (string name, T def) {
  if (__testlib_opts.count(name))
    return opt<T>(name);
  return def;
}

int main (int argc, char **argv) {
  registerGen(argc, argv, 1);

  int n = opt<int>("n", 0);
  int m = opt<int>("m", 0);
  int K = opt<int>("k");
  int rK = opt<int>("rk", K);
  int groupc = opt<int>("gs");
  int gc = opt<int>("gc");
  
  double portal_coin_prob = opt<double>("pcp");
  double extra_coin_prob = opt<double>("ecp");
  double free_space_prob = opt<double>("fsp");
  bool no_extra = opt<bool>("noextra");
  
  int force_start_portal = opt<int>("sp");

  int mode = opt<int>("mode", 0); // 0 = random trees, 1 = stripes, 2 = one line
  
  assert(rK % gc == 0);
  assert(groupc >= gc);

  // portals [0, rK) get assigned to groups based on their mod value
  // portals [rK, K) are isolated from the rest of the portals in a separate group
  vector<int> portal_perm (K);

  // generate portal_perm [0, rK)
  vector<vector<int>> frees (gc, vector<int> (0));
  for (int i = 0; i < rK; i++)
    frees[i % gc].push_back(i);

  for (int i = 0; i < gc; i++)
    shuffle(frees[i].begin(), frees[i].end());

  for (int i = 0; i < rK; i++) {
    portal_perm[i] = frees[(i + 1) % gc].back();
    frees[(i + 1) % gc].pop_back();
  }

  // generate portal_perm [rK, K)
  if (rK < K) {
    iota(portal_perm.begin() + rK, portal_perm.end(), rK);
    shuffle(portal_perm.begin() + rK, portal_perm.end());
  }

  AbstractTest test;
  test.groups = vector<AbstractGroup> (groupc + (int) (rK < K));
  test.portal_perm = portal_perm;

  for (int i = 0; i < K; i++) {
    int group_id;
    if (i < rK) {
      int choices = ceilf(groupc - (i % gc), gc);
      group_id = (i % gc) + gc * rnd.next(choices);
    } else {
      group_id = groupc;
    }

    AbstractPortal portal;
    portal.index = i;
    if (rnd.next(1.0) < portal_coin_prob)
      portal.coin_value = rnd.next(1, 1'000'000'000);
    else
      portal.coin_value = {};

    test.groups[group_id].portals.push_back(portal);
  }

  if (force_start_portal == -1) {
    test.groups.push_back(AbstractGroup {.start = true});
  }

  if (!no_extra) {
    for (auto &group : test.groups) {
      group.free_space = rnd.next(2 * (int) (1 + group.portals.size() * free_space_prob));
      int extra_coin_count = rnd.next(2 * (int) (1 + group.portals.size() * extra_coin_prob));
      for (int i = 0; i < extra_coin_count; i++)
        group.extra_coins.push_back(rnd.next(1, 1'000'000'000));
    }
  }

  if (force_start_portal != -1) {
    while (true) {
      int id = rnd.next(groupc);
      if (test.groups[id].portals.empty() && force_start_portal == 1)
        continue;

      test.groups[id].start = true;
      break;
    }
  }

  Test T;
  if (mode == 0) {
    assert(n != 0);
    assert(m != 0);
    T = generate_grid_bfs(test, n, m);
  } else if (mode == 1) {
    T = generate_grid_stripy(test);
  } else if (mode == 2) {
    T = generate_grid_horizontal(test);
  } else {
    assert(false);
  }
  
  permute_test(T);
  cout << T; 
}
