#include <iostream>
using namespace std;

int main() {
	// loeme indikaatorite arvu
	int n;
	cin >> n;

	// lahendame kõik testid
	for (;;) {
		long long code;
		cin >> code;

		// kui rohkem teste pole, lõpetame
		if (code == -1) {
			break;
		}

		// TODO: küsime lisainfot, kuni leiame selle testi vastuse
		for (int i = 0; i < 4; ++i) {
			cout << "NEXT" << endl;
			cin >> code;
		}

		// TODO: väljastame vastuse ja liigume järgmise testi juurde
		cout << 42 << endl;
	}
}
