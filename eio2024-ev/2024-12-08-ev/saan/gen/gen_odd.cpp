#include <cstdint>
#include "testlib.h"
#include <iostream>

using namespace std;

int main (int argc, char **argv) {
  registerGen(argc, argv, 1);

  int n = opt<int>("n");
  vector<int> arr;
  for (int i = 1; i <= n; i += 2)
    arr.push_back(i);

  cout << n << " " << (int) arr.size() << '\n';
  for (int i = 0; i < (int) arr.size(); i++) {
    cout << arr[i];
    if (i != (int) arr.size() - 1)
      cout << " ";
  }
  cout << '\n';
}
