#include <iostream>
#include <vector>

using namespace std;

const int MAX_N = 305;

int grid2[MAX_N][MAX_N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    int tot = 0;
    int best = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> grid2[i][j];
            grid2[i][j] -= 50;
             
            tot += grid2[i][j];
        }
    }

    for (int i1 = 1; i1 <= n; i1++) {
        for (int i2 = i1; i2 <= n; i2++) {
            for (int j1 = 1; j1 <= n; j1++) {
                for (int j2 = j1; j2 <= n; j2++) {
                    int sum = 0;
                    for (int i3 = i1; i3 <= i2; i3++) {
                        for (int j3 = j1; j3 <= j2; j3++) {
                            sum += grid2[i3][j3];
                        }
                    }

                    if (tot - sum > best)
                    {
                        best = tot - sum;
                    }
                }
            }
        }
    }

    cout << best << '\n';
    return 0;
}
