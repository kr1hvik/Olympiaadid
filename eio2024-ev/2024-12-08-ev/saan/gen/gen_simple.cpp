// simple generator - n and k are given, test is a random subset

#include <cstdint>
#include "testlib.h"
#include <numeric>

int main (int argc, char **argv) {
  registerGen(argc, argv, 1);

  int n = opt<int>("n");
  int K = opt<int>("K");

  std::vector<int> perm (n);
  std::iota(perm.begin(), perm.end(), 1);
  shuffle(perm.begin(), perm.end());

  std::vector<int> arr (perm.begin(), perm.begin() + K);
  std::sort(arr.begin(), arr.end());

  std::cout << n << " " << K << '\n';
  for (int i = 0; i < K; i++) {
    std::cout << arr[i];
    if (i != K - 1)
      std::cout << " ";
  }
  std::cout << '\n';
}
