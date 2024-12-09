// n and k are given
// wn biases the choice for each new integer in the subset
// negative wn makes occupied seats to be more likely in the ends
// positive wn makes occupied seats to be more likely in the middle

#include <cstdint>
#include "testlib.h"
#include <cassert>
#include <set>

int roll (int n, int wn) {
  int dist = rnd.wnext((n + 1) / 2, wn);
  if (rnd.next(2))
    return std::min(1 + dist, n);
  return std::max(n - dist, 1);
}

int main (int argc, char **argv) {
  registerGen(argc, argv, 1);

  int n = opt<int>("n");
  int K = opt<int>("K");
  int wn = opt<int>("wn");

  std::set<int> occ;
  while ((int) occ.size() < K) {
    int cur = roll(n, wn);
    occ.insert(cur);
  }

  std::vector<int> arr (occ.begin(), occ.end());
  std::cout << n << " " << K << '\n';
  for (int i = 0; i < K; i++) {
    std::cout << arr[i];
    if (i != K - 1)
      std::cout << " ";
  }
  std::cout << '\n';
}
