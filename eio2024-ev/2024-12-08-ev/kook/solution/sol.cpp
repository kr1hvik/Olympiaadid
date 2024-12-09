// taislahendus
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<pair<int,int>> p(n), m(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i].first;
        p[i].second = i;
    }
    for (int i = 0; i < n; ++i) {
        cin >> m[i].first;
        m[i].second = i;
    }

    sort(p.begin(), p.end());
    sort(m.begin(), m.end());

    bool voimalik = 1;
    for (int i = 1; i < n; ++i) {
        if (m[i].first * p[i-1].first != m[i-1].first * p[i].first) {
            voimalik = 0;
            break;
        }
    }

    if (voimalik) {
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            a[m[i].second] = p[i].second+1;
        }
        cout << "JAH\n";
        for (int i = 0; i < n; ++i) {
            cout << a[i] << " \n"[i==n-1];
        }
    }
    else {
        cout << "EI\n";
    }

    return 0;
}