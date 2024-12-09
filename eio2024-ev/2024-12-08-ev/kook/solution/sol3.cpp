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

    vector<int> p_sort = p, m_sort = m;
    sort(p_sort.begin(), p_sort.end());
    sort(m_sort.begin(), m_sort.end());

    bool voimalik = 1;
    for (int i = 1; i < n; ++i) {
        if (m_sort[i]*p_sort[i-1] != m_sort[i-1]*p_sort[i]) {
            voimalik = 0;
            break;
        }
    }

    if (voimalik) {
        cout << "JAH\n";
        vector<int> a(n);

        vector<bool> p_voetud(n, 0), m_voetud(n, 0);

        for (int i = 0; i < n; ++i) {
            int p_vota = -1, m_vota = -1;

            for (int j = 0; j < n; ++j) {
                if (p[j] == p_sort[i]) {
                    p_vota = j;
                    break;
                }
            }

            for (int j = 0; j < n; ++j) {
                if (m[j] == m_sort[i]) {
                    m_vota = j;
                    break;
                }
            }

            a[m_vota] = p_vota+1;

            p[p_vota] = -1;
            m[m_vota] = -1;
        }

        for (int i = 0; i < n; ++i) {
            cout << a[i] << " \n"[i==n-1];
        }
    }
    else {
        cout << "EI\n";
    }

    return 0;
}