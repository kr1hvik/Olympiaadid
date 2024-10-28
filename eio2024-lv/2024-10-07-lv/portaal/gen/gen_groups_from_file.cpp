// like gen_groups, but instead of generating the groups, just reads them from a file

#include "gen_grid.h"

#include <fstream>

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
  
  double portal_coin_prob = opt<double>("pcp");
  double extra_coin_prob = opt<double>("ecp");
  double free_space_prob = opt<double>("fsp");
  bool no_extra = opt<bool>("noextra");
  
  int force_start_portal = opt<int>("sp");
  int mode = opt<int>("mode", 0); // 0 = random trees, 1 = stripes, 2 = one line

  string src = opt<string>("src");
  ifstream sin (src.c_str());

  int K, groupc;
  sin >> K >> groupc;

  vector<int> portal_perm (K);
  for (int i = 0; i < K; i++)
    sin >> portal_perm[i];

  vector<int> group_id (K);
  for (int i = 0; i < K; i++)
    sin >> group_id[i];
  
  AbstractTest test;
  test.groups = vector<AbstractGroup> (groupc);
  test.portal_perm = portal_perm;

  for (int i = 0; i < K; i++) {
    AbstractPortal portal;
    portal.index = i;
    if (rnd.next(1.0) < portal_coin_prob)
      portal.coin_value = rnd.next(1, 1'000'000'000);
    else
      portal.coin_value = {};

    test.groups[group_id[i]].portals.push_back(portal);
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

