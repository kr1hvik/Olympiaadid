#include <iostream>
#include <vector>

using namespace std;

const int MAX_N = 305;

int grid [MAX_N][MAX_N];

int main () {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n;
  cin >> n;

  int tot = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> grid[i][j];
      grid[i][j] -= 50;

      tot += grid[i][j];
    }
  }

  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      grid[i][j] += grid[i][j - 1];

  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      grid[i][j] += grid[i - 1][j];

  int ans = 0;
  for (int i1 = 0; i1 < n; i1++) {
    for (int i2 = i1 + 1; i2 <= n; i2++) {
      int cur = 0;
      for (int j = 0; j <= n; j++) {
        ans = min(ans, grid[i2][j] - grid[i1][j] - cur);
        cur = max(cur, grid[i2][j] - grid[i1][j]);
      }
    }
  }

  ans = tot - ans;
  cout << ans << '\n';
}
