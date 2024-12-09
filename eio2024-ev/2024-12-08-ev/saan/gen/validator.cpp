#include "testlib.h"

#include <vector>

const int MAX_N = 90; // temporary, change to whatever is actually maxn eventually

int main (int argc, char **argv) {
  registerValidation(argc, argv);

  int n = inf.readInt(1, MAX_N, "n");
  inf.readSpace();
  int k = inf.readInt(1, n, "k");
  inf.readEoln();

  std::vector<int> arr (k);
  for (int i = 0; i < k; i++) {
    arr[i] = inf.readInt(1, n, "ai");
    if (i != k - 1)
      inf.readSpace();
  }

  inf.readEoln();

  for (int i = 0; i < k - 1; i++) {
    ensuref(arr[i] < arr[i + 1], "A not increasing");
  }
  inf.readEof();
}
