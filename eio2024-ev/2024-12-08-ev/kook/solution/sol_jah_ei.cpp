// vastab ainult jah/ei
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> p(n), m(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> m[i];
    }

    sort(p.begin(), p.end());
    sort(m.begin(), m.end());

    bool voimalik = 1;
    for (int i = 1; i < n; ++i) {
        if (m[i] * p[i-1] != m[i-1] * p[i]) {
            voimalik = 0;
            break;
        }
    }

    if (voimalik) {
        cout << "JAH\n";
    }
    else {
        cout << "EI\n";
    }

    return 0;
}