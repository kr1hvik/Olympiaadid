#include <iostream>
#include <algorithm>

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
    sort(b, b + n, greater<int>());
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
                while (l < n && b[n - l - 1] + a[k] <= s) {
                    l++;
                }
                p *= l - (l >= n - j) - k + (k > i);
                if (p <= 0) {
                    p = 0;
                    break;
                }
                p %= mod;
            }
            ans += p;
            ans %= mod;
        }
        cout << ans << endl;
    }
}
