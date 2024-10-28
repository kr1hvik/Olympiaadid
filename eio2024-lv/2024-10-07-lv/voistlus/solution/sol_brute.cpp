#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int n;
    cin >> n;
    int i;
    int a[n];
    int b[n];
    int perm[n];
    for (i = 0; i < n; i++) {
        cin >> a[i];
        perm[i] = i;
    }
    for (i = 0; i < n; i++) {
        cin >> b[i];
    }
    int ans[n] = {0};
    do {
        int mx = 0;
        for (i = 0; i < n; i++) {
            mx = max(mx, a[i] + b[perm[i]]);
        }
        for (i = 0; i < n; i++) {
            if (a[i] + b[perm[i]] == mx) {
                ans[i]++;
            }
        }
    } while (next_permutation(perm, perm + n));
    for (i = 0; i < n; i++) {
        cout << ans[i] << endl;
    }
}
