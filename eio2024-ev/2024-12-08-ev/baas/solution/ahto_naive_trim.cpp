// naiivne lahendus: võrdleb esimese rea iga sõna kõigi järgmiste ridade kõigi sõnadega
// realisatsioon püüab optimeerida sellega, et iga järgmise reaga võrreldakse ainult eelmiste ridadega võrdlemise järel veel alles jäänud prefiksit
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
		string file_pref = words[0][k];
		for (int i = 1; i < n; ++i) {
			int line_pref = 0;
			for (int j = 0; j < m; ++j) {
				int word_pref = prefix(file_pref, words[i][j]);
				if (line_pref < word_pref) {
					line_pref = word_pref;
				}
			}
			if (file_pref.length() > line_pref) {
				file_pref = file_pref.substr(0, line_pref);
			}
		}
		if (best.length() < file_pref.length() or best.length() == file_pref.length() and best > file_pref) {
			best = file_pref;
		}
	}
	cout << best << '\n';
}
