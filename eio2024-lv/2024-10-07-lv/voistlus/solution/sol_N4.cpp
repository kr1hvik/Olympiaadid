#include <iostream>

using namespace std;

int main()
{
    long long mod = 1e9+7;
    int n;
    cin >> n;
    int i, j, k, l;
    int a[n];
    int b[n];
    for (i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (i = 0; i < n; i++) {
        cin >> b[i];
    }
    for (i = 0; i < n; i++) {
        long long ans = 0;
        for (j = 0; j < n; j++) {
            long long p = 1;
            int s = a[i] + b[j];
            l = 0;
            for (k = 0; k < n; k++) {
                if (k == i) {
                    continue;
                }
                int q = 0;
                for (l = 0; l < n; l++) {
                    if (l == j) {
                        continue;
                    }
                    if (a[k] + b[l] <= s) {
                        q++;
                    }
                }
                if (k < i) {
                    q -= k;
                }
                else {
                    q -= k - 1;
                }
                p *= max(q, 0);
                p %= mod;
            }
            ans += p;
            ans %= mod;
        }
        cout << ans << endl;
    }
}
