// naiivne lahendus: võrdleb esimese rea iga sõna kõigi järgmiste ridade kõigi sõnadega
// natuke optimeeritud realisatsioon: edastab tekste funktsioonile viitena ja hoiab vahetulemustena tekside asemel nende pikkuseid
// mõnes testis töötab 2-3 korda kiiremini, aga punkte juurde siiski ei saa

#include <iostream>
#include <string>
#include <vector>
using namespace std;

int prefix(const string & a, const string & b) {
	unsigned i = 0;
	while (i < a.length() and i < b.length() and a[i] == b[i]) {
		++i;
	}
	return i;
}

int main() {
	int m, n;
	cin >> m >> n;
	vector<vector<string>> words(n);
	for (int i = 0; i < n; ++i) {
		words[i].resize(m);
		for (int j = 0; j < m; ++j) {
			cin >> words[i][j];
		}
	}

	string best;
	for (int k = 0; k < m; ++k) {
		int file_pref = words[0][k].length();
		for (int i = 1; i < n; ++i) {
			int line_pref = 0;
			for (int j = 0; j < m; ++j) {
				int word_pref = prefix(words[0][k], words[i][j]);
				if (line_pref < word_pref) {
					line_pref = word_pref;
				}
			}
			if (file_pref > line_pref) {
				file_pref = line_pref;
			}
		}
		if (best.length() < file_pref or best.length() == file_pref and best > words[0][k].substr(0, file_pref)) {
			best = words[0][k].substr(0, file_pref);
		}
	}
	cout << best << '\n';
}
