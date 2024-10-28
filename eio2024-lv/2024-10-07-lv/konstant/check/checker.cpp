#include "testlib.h"

using namespace std;

int main (int argc, char **argv) {
  registerTestlibCmd(argc, argv);

  int subtask_num = inf.readInt();

  while (!ans.seekEof() && !ouf.seekEof()) {
    long long j = ans.readLong();
    long long p = ouf.readLong();
    if (subtask_num == 4 && p == -1)
      quitf(_wa, "Operation limit (1 000 000) exceeded");
    if (j != p)
      quitf(_wa, "translate:wrong");
  }

  if (!ans.seekEof() || !ouf.seekEof())
    quitf(_wa, "translate:wrong");

  quitf(_ok, "translate:success");
}
