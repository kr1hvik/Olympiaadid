#include <cstdint>
#include "testlib.h"
#include <set>
#include <vector>

int main (int argc, char **argv) {
  registerGen(argc, argv, 1);

  int n = opt<int>("n");
  int K = opt<int>("K");
  int wn = opt<int>("wn");

  std::set<int> seats;
  while (seats.size() < K) {
    seats.insert(rnd.wnext(n, wn));
  }

  std::vector<int> arr (seats.begin(), seats.end());
  
  std::cout << n << " " << K << '\n';
  for (int i = 0; i < K; i++) {
    std::cout << 1 + arr[i];
    if (i != K - 1)
      std::cout << " ";
  }
  std::cout << '\n';
}
