// 2017-11-18 programmeerimisvõistlus
// Ülesanne: MAKSIMAALNE TÕUS
// Autor: Ahto Truu
// Testitud: GCC 6.4.0 / CygWin

// Lihtne lahendus O(N^2) ajaga:
// vaatab ükshaaval läbi raja kõik punktid;
// leiab igas punktis sellest algava tõusu lõpu.

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
	for (int i1 = 0; i1 < n; ++i1) {
		for (int i2 = i1 + 1; i2 < n; ++i2) {
			if (h[i2 - 1] >= h[i2]) {
				// ei ole enam tõus, katkestame
				break;
			}
			if (hm < h[i2] - h[i1]) {
				hm = h[i2] - h[i1];
			}
		}
	}

	val << hm << '\n';
	return 0;
}
