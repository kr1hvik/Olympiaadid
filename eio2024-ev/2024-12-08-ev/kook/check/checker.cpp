#include "testlib.h"
#include <vector>
using namespace std;

int main (int argc, char **argv) {
  registerTestlibCmd(argc, argv);

  int n = inf.readInt();

  string oige_toevaartus = ans.readString();
  string opilase_toevaartus = ouf.readString();

  if (opilase_toevaartus != "JAH" && opilase_toevaartus != "EI") {
    quitf(_pe, "First line should be JAH or EI");
  }

  if (opilase_toevaartus != oige_toevaartus) {
    quitf(_wa, "Wrong answer");
  }
  first_test_passed = 1;

  if (oige_toevaartus == "EI") {
    if (!ouf.seekEof()) {
      quitf(_pe, "Extra data at end of file");
    }
    quitf(_ok, "OK");
  }

  vector<int> opilase_jarjekord(n, 0);
  vector<bool> olemas(n+1, 0);
  for (int i = 0; i < n; ++i) {
    opilase_jarjekord[i] = ouf.readInt(1, n, "Table index");
    if (olemas[opilase_jarjekord[i]]) {
      quitf(_pe, "Duplicate table index");
    }
    olemas[opilase_jarjekord[i]] = 1;
  }

  vector<int> p = inf.readIntegers(n, 1, 1000, "P_i");
  vector<int> m = inf.readIntegers(n, 1, 1000, "M_i");

  for (int i = 1; i < n; ++i) {
    int prev = opilase_jarjekord[i-1]-1;
    int cur = opilase_jarjekord[i]-1;
    if (m[i-1] * p[cur] != m[i] * p[prev]) {
      quitf(_partially, "Assignment to tables is incorrect");
    } 
  }

  if (!ouf.seekEof()) {
    quitf(_pe, "Extra data at end of file");
  }
  quitf(_ok, "OK");
}
