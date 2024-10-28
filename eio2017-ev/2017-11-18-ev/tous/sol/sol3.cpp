// 2017-11-18 programmeerimisvõistlus
// Ülesanne: MAKSIMAALNE TÕUS
// Autor: Ahto Truu
// Testitud: GCC 6.4.0 / CygWin

// Efektiivne lahendus O(N) ajaga:
// vaatab ükshaaval läbi raja kõik punktid;
// leiab igas punktis sellest algava tõusu lõpu;
// otsib uut tõusu eelmise lõpust alates.

#include <fstream>
#include <vector>
using namespace std;

ifstream sis("toussis.txt");
ofstream val("tousval.txt");

int n; // raja pikkus
vector<int> h; // rajaprofiil

int main() {
	sis >> n;
	h.resize(n);
	for (int i = 0; i < n; ++i) {
		sis >> h[i];
	}

	int hm = 0; // seni maksimaalne tõus
	int i1 = 0;
	while (i1 < n) {
		int i2 = i1 + 1;
		while (i2 < n && h[i2 - 1] < h[i2]) {
			if (hm < h[i2] - h[i1]) {
				hm = h[i2] - h[i1];
			}
			i2 += 1;
		}
		i1 = i2;
	}

	val << hm << '\n';
	return 0;
}
