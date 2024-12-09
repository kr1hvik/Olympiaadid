#include <iostream>

using namespace std;

typedef long long ll;

// the mean must be (0 + 1 + ... + (n - 1)) / n  =  (n - 1) / 2
// sum must be   k (n - 1) / 2

bool is_balanced (ll mask, int n) {
  int sum = 0;
  for (int i = 0; i < n; i++)
    if (mask & 1 << i)
      sum += i;

  return 2 * sum == __builtin_popcountll(mask) * (n - 1);
}

int main () {
  int n, K;
  cin >> n >> K;

  ll goodbits = 0;
  for (int i = 0; i < K; i++) {
    int a;
    cin >> a;
    a--;

    goodbits |= 1LL << a;
  }

  int ans = n + 1;
  ll ways = 0;
  for (ll mask = 0; mask < 1LL << n; mask++) {
    if (__builtin_popcountll(mask) != K)
      continue;

    if (!is_balanced(mask, n))
      continue;

    int cur = __builtin_popcountll(goodbits ^ mask) / 2;
    if (cur < ans) {
      ans = cur;
      ways = 1;
      cerr << " " << cur << " " << mask << '\n';
    } else if (cur == ans) {
      cerr << " " << cur << " " << mask << '\n';
      ways++;
    }
  }

  if (ans > n)
    cout << -1 << '\n';
  else
    cout << ans << '\n';

  cout << ways << '\n';
}
