// almost balanced (only at most p moves away from perfection)
// right side values close to the middle
// left side values far from the middle
// left side values added until their leverage is greater than W
// n always odd

#include <cstdint>
#include "testlib.h"
#include <cassert>
#include <algorithm>

int main (int argc, char **argv) {
  registerGen(argc, argv, 1);

  int n = opt<int>("n");
  assert(n % 2 == 1);
  
  int p = opt<int>("p");
  int W = opt<int>("W");

  std::vector<std::pair<int, int>> left; // leverage, index
  std::vector<std::pair<int, int>> right; // leverage, index
  for (int i = 0; i < n; i++) {
    int lever = 2 * i - n + 1;

    if (lever == 0)
      continue;

    if (lever < 0)
      left.emplace_back(lever, i);
    else
      right.emplace_back(lever, i);
  }

  std::vector<int> arr;
  int bal = 0;
  for (auto p : right) {
    if (bal > W)
      break;

    bal += p.first;
    arr.push_back(p.second);
  }

  assert(bal > W);
  
  for (auto p : left) {
    if (bal + p.first >= 0) {
      bal += p.first;
      arr.push_back(p.second);
    }
  }

  assert(bal == 0);

  int K = arr.size();
  for (int i = 0; i < p; i++) {
    int idx = rnd.next(K);
    arr.erase(arr.begin() + idx); // quadratic ok, n small

    while (true) {
      int nu = rnd.next(n);
      if (std::find(arr.begin(), arr.end(), nu) == arr.end()) {
        arr.push_back(nu);
        break;
      }
    }
  }

  std::sort(arr.begin(), arr.end());
  assert(arr.size() == K);

  std::cout << n << " " << K << '\n';
  for (int i = 0; i < K; i++) {
    std::cout << 1 + arr[i];
    if (i != K - 1)
      std::cout << " ";
  }
  std::cout << '\n';
}
