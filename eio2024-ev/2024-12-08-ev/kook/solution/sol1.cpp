#include <iostream>
#include <vector>
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

    if (m[0] * p[0] == m[1] * p[1]) {
        cout << "JAH\n2 1\n";
    }
    else if (m[0] * p[1] == m[1] * p[0]) {
        cout << "JAH\n1 2\n";
    }
    else {
        cout << "EI\n";
    }

    return 0;
}