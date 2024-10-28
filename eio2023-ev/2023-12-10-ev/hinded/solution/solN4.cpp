#include <iostream>
#include <vector>

using namespace std;

const int MAX_N = 305;

int grid[MAX_N][MAX_N];
int sums[MAX_N][MAX_N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    int tot = 0;
    int best = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> grid[i][j];
            grid[i][j] -= 50;

            tot += grid[i][j];
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            sums[i][j] = sums[i][j - 1] + sums[i - 1][j] - sums[i - 1][j - 1] + grid[i][j];
        }

    }

    for (int i1 = 1; i1 <= n; i1++) {
        for (int j1 = 1; j1 <= n; j1++) {
            for (int i2 = 0; i2 <= i1; i2++) {
                for (int j2 = 0; j2 <= j1; j2++) {
                    int sum = sums[i1][j1] - sums[i1][j2] - sums[i2][j1] + sums[i2][j2];

                    if (tot - sum > best)
                    {
                        best = tot - sum;
                    }
                }
            }
        }
    }

    cout << best << '\n';
}
