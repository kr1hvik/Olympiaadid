#include <iostream>
using namespace std;

int main() {
	// loeme sisendandmed
	double x, y, n;
	cin >> x >> y >> n;
	x /= 100; y /= 100; // X ja Y sentidest eurodeks

	// leiame ja väljastame vastuse
	if (4 * x + 5 * y < n) {
		// raha jätkub, et tulesid põlemas hoida
		// kojujõudmisest magamaminekuni
		cout << 9 << '\n';
	} else if (x < y) {
		// päevane elekter on odavam
		// kasutame seda nii palju kui võimalik
		if (4 * x > n) {
			// kogu raha kulub päevasel ajal ära
			cout << n / x << '\n';
		} else {
			// raha jätkub, et tulesid põlemas hoida
			// kõik 4 päevast tundi; leiame, kui
			// palju õhtuks üle jääb
			double varu = n - 4 * x;
			cout << 4 + varu / y << '\n';
		}
	} else {
		// õhtune elekter on odavam
		// kasutame seda nii palju kui võimalik
		if (5 * y > n) {
			// kogu raha kulub õhtusel ajal ära
			cout << n / y << '\n';
		} else {
			// raha jätkub, et tulesid põlemas hoida
			// kõik 5 õhtust tundi; leiame, kui
			// palju päevaks üle jääb
			double varu = n - 5 * y;
			cout << 5 + varu / x << '\n';
		}
	}
}
