// O(N^5) dp

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

typedef long long ll;

int main () {
  int n, K;
  cin >> n >> K;

  vector<int> good (n, 0);
  for (int i = 0; i < K; i++) {
    int x;
    cin >> x;

    good[x - 1] = 1;
  }
  
  vector<vector<vector<ll>>> dp (n + 1, vector<vector<ll>> (n + 1, vector<ll> (n * n + 1, 0)));
  // # placed, # bad, sum
  dp[0][0][0] = 1;

  for (int i = 0; i < n; i++) {
    // try placing i

    for (int j = n - 1; j >= 0; j--) {
      for (int k = n - 1; k >= 0; k--) {
        for (int S = n * n - i; S >= 0; S--) {
          dp[j + 1][k + !good[i]][S + i] += dp[j][k][S];
        }
      }
    }
  }

  if (K * (n - 1) % 2 == 1) {
    cout << -1 << '\n';
    cout << 0 << '\n';
    return 0;
  }
  
  int good_S = K * (n - 1) / 2;
  for (int k = 0; k <= n; k++) {
    if (dp[K][k][good_S] != 0) {
      cout << k << '\n';
      cout << dp[K][k][good_S] << '\n';
      return 0;
    }
  }

  assert(false);
}
