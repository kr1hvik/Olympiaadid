// naiivne lahendus: võrdleb esimese rea iga sõna kõigi järgmiste ridade kõigi sõnadega
// naiivne realisatsioon: hoiab kõiki vahetulemusi tekstidena ja kopeerib neid edasi-tagasi
// optimeerib sisendi lugemise, aga see midagi ei muuda

#include <iostream>
#include <string>
#include <vector>
using namespace std;

string prefix(string a, string b) {
	unsigned i = 0;
	while (i < a.length() and i < b.length() and a[i] == b[i]) {
		++i;
	}
	return a.substr(0, i);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int m, n;
	cin >> m >> n;
	vector<vector<string>> words(n);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			string w;
			cin >> w;
			words[i].push_back(w);
		}
	}

	string best;
	for (int k = 0; k < m; ++k) {
		string file_pref = words[0][k];
		for (int i = 1; i < n; ++i) {
			string line_pref;
			for (int j = 0; j < m; ++j) {
				string word_pref = prefix(words[0][k], words[i][j]);
				if (line_pref.length() < word_pref.length()) {
					line_pref = word_pref;
				}
			}
			if (file_pref.length() > line_pref.length()) {
				file_pref = line_pref;
			}
		}
		if (best.length() < file_pref.length() or best.length() == file_pref.length() and best > file_pref) {
			best = file_pref;
		}
	}
	cout << best << '\n';
}
