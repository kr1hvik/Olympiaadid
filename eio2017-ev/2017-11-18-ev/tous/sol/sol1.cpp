// 2017-11-18 programmeerimisvõistlus
// Ülesanne: MAKSIMAALNE TÕUS
// Autor: Ahto Truu
// Testitud: GCC 6.4.0 / CygWin

// Väga naiivne lahendus O(N^3) ajaga:
// vaatab ükshaaval läbi raja kõik lõigud;
// kontrollib iga lõigu kohta, kas see on tõus.

#include <fstream>
#include <vector>
using namespace std;

ifstream sis("toussis.txt");
ofstream val("tousval.txt");

int n; // raja pikkus
vector<int> h; // rajaprofiil

// kontrollib, kas h[i1] < ... < h[i2]
bool tous(int i1, int i2) {
	for (int i = i1; i < i2; ++i) {
		if (h[i] >= h[i + 1]) {
			return false;
		}
	}
	return true;
}

int main() {
	sis >> n;
	h.resize(n);
	for (int i = 0; i < n; ++i) {
		sis >> h[i];
	}

	int hm = 0; // seni maksimaalne tõus
	for (int i1 = 0; i1 < n; ++i1) {
		for (int i2 = i1 + 1; i2 < n; ++i2) {
			if (tous(i1, i2)) {
				if (hm < h[i2] - h[i1]) {
					hm = h[i2] - h[i1];
				}
			}
		}
	}

	val << hm << '\n';
	return 0;
}
