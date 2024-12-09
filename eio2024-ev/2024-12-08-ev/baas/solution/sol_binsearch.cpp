#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

unordered_set<string> vota_sobivad(const vector<string> &rida, int l) {
    unordered_set<string> sobivad;
    for(auto &x : rida) {
        if(x.length() >= l) {
            sobivad.insert(x.substr(0, l));
        }
    }
    return sobivad;
}

unordered_set<string> proovi(const vector<vector<string>> &read, int l) {
    // Kas pikkus sobib?
    // Kui jah, siis anna sobivad sõned ka
    unordered_set<string> sobivad = vota_sobivad(read[0], l);
    for(const auto &rida : read) {
        unordered_set<string> praegu = vota_sobivad(rida, l);
        // Ühilda
        for(auto it = sobivad.begin(); it != sobivad.end();) {
            if(praegu.count(*it) == 0) {
                it = sobivad.erase(it);
            } else {
                ++ it;
            }
        }
    }
    return sobivad;
} 

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    vector<vector<string>> read(m);
    for(auto &rida : read) {
        rida.resize(n);
        for(auto &s : rida) {
            cin >> s;
        }
    }

    // Otsi pikkus
    int lo = 1, hi = 101;
    while(hi - lo > 1) {
        int m = (lo + hi) / 2;
        auto sobivad = proovi(read, m);
        if(sobivad.empty()) {
            hi = m;
        } else {
            lo = m;
        }
    }

    // Minimaalne sõne
    auto sobivad = proovi(read, lo);
    const string *mi = &*sobivad.begin();
    for(auto &s : sobivad) {
        if(s < *mi) {
            mi = &s;
        }
    }
    cout << *mi << '\n';
}