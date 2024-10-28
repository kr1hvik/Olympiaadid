// 2017-11-18 programmeerimisvõistlus
// Ülesanne: MAKSIMAALNE TÕUS
// Autor: Ahto Truu
// Testitud: GCC 6.4.0 / CygWin

// Optimaalne lahendus O(N) ajaga ja O(1) mäluga:
// loeb punktid ükshaaval sisse ja peab jooksvalt
// meeles eelmise punkti kõrguse ja jooksva tõusu
// alguse; nii saab iga punkti kohta otsustada,
// kas tõus jätkub ja kui kõrge see juba on.

#include <fstream>
using namespace std;

ifstream sis("toussis.txt");
ofstream val("tousval.txt");

int main() {
	int n;
	sis >> n;

	int hm = 0; // seni maksimaalne tõus
	int hp; // praeguse tõusu algus
	int he; // eelmise punkti kõrgus
	for (int i = 0; i < n; ++i) {
		int h; // uue punkti kõrgus
		sis >> h;
		if (i == 0) {
			// kõige esimene rajapunkt
			hp = h;
		} else if (he < h) {
			// tõus jätkub
			if (hm < h - hp) {
				// uus rekord, jätame meelde
				hm = h - hp;
			}
		} else {
			// tõusu lõpp, aga siit võib alata uus tõus
			hp = h;
		}
		// uus punkt saab nüüd eelmiseks
		he = h;
	}

	val << hm << '\n';
	return 0;
}
