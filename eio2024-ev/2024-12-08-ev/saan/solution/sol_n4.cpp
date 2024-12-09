// O(n^4) dp

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

template<typename T>
class OffsetArray {
  int offset;
  vector<T> vec;

public:
  OffsetArray (int _size, int _offset, T init) : offset(_offset), vec(_size, init) { }

  T& operator[] (int index) {
    return vec[offset + index];
  }
};

const int INF = 1e9 + 5;

typedef long long ll;

struct State {
  int steps;
  ll ways;
  
  State (int _steps = INF, ll _ways = 0) : steps(_steps), ways(_ways) { }

  void merge_from (const State &oth) {
    if (oth.steps < steps) {
      steps = oth.steps;
      ways = oth.ways;
    } else if (oth.steps == steps) {
      ways += oth.ways;
    }
  }
};

int main () {
  int n, K;
  cin >> n >> K;

  vector<int> good (n, 0);
  for (int i = 0; i < K; i++) {
    int x;
    cin >> x;

    good[x - 1] = 1;
  }

  // position, difference, sum
  OffsetArray<vector<State>> dp (2 * n + 1, n, vector<State> (n * n + 1, State()));
  dp[0][0] = State(0, 1);

  for (int i = 0; i < n; i++) {
    OffsetArray<vector<State>> ndp (2 * n + 1, n, vector<State> (n * n + 1, State()));
    
    for (int j = -n; j <= n; j++) {
      for (int S = 0; S <= n * n; S++) {
        if (dp[j][S].steps == INF)
          continue;

        if (good[i]) {
          // currently occupied

          // do nothing
          if (S + i <= n * n)
            ndp[j][S + i].merge_from(dp[j][S]);
          
          // try removing them
          if (j + 1 <= n)
            ndp[j + 1][S].merge_from(dp[j][S]);
        } else {
          // currently unoccupied

          // do nothing
          ndp[j][S].merge_from(dp[j][S]);

          // try adding something here
          if (j - 1 >= -n && S + i <= n * n)
            ndp[j - 1][S + i].merge_from(State(dp[j][S].steps + 1, dp[j][S].ways));
        }
      }
    }

    dp = ndp;
  }

  if (K * (n - 1) % 2 == 1) {
    cout << -1 << '\n';
    cout << 0 << '\n';
    return 0;
  }

  int good_S = K * (n - 1) / 2;
  cout << dp[0][good_S].steps << '\n' << dp[0][good_S].ways << '\n';
}
