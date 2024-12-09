// input is just the first K elements

#include "testlib.h"

int main (int argc, char **argv) {
  registerGen(argc, argv, 1);

  int n = opt<int>("n");
  int K = opt<int>("K");

  std::cout << n << " " << K << '\n';
  for (int i = 1; i <= K; i++) {
    std::cout << i;
    if (i != K)
      std::cout << " ";
  }
  std::cout << '\n';
}
