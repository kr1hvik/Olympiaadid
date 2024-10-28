// 2017-11-18 programmeerimisvõistlus
// Ülesanne: MURDUDE LAHUTAMINE
// Autor: Ahto Truu
// Testitud: GCC 6.4.0 / CygWin

#include <fstream>
#include <string>
using namespace std;

ifstream sis("murdsis.txt");
ofstream val("murdval.txt");

int main() {
	// loeme sisendi
	int a, b, c, d;
	char e;
	sis >> a >> e >> b;
	sis >> c >> e >> d;

	// viime ühisele nimetajale b * d ja lahutame
	int x = a * d - c * b, y = b * d;

	// jätame meelde tulemuse märgi ja arvutame edasi absoluutväärtusega
	bool n;
	if (x < 0) {
		n = true;
		x = -x;
	} else {
		n = false;
	}

	// leiame suurima ühisteguri: selle ülesande väikeste arvude korral
	// on kõigi võimalike tegurite proovimine piisavalt kiire
	int t;
	for (int i = 1; i <= y; ++i) {
		if (x % i == 0 && y % i == 0) {
			t = i;
		}
	}
	// efektiivsem oleks kasutada Eukleidese algoritmi
	// int t = x;
	// for (int u = y; u > 0; ) {
	//     int v = t % u;
	//     t = u; u = v;
	// }
	// C++17's (GCC 7.x) on olemas ka standardfunktsioonid gcd, lcm
	// #include <numeric>
	// using namespace std;
	// int t = gcd(x, y);

	// taandame
	x = x / t;
	y = y / t;

	// eraldame täis- ja murdosa
	int z = x / y;
	x = x % y;

	// formaatimata tulemus: täisosa
	if (n) {
		val << '-';
	}
	val << z << '\n';

	// formaatimata tulemus: murdosa
	if (x != 0) {
		val << x << '/' << y;
	}
	val << '\n';

	// formaaditud tulemus
	if (x != 0) {
		// kõik arvud tekstideks
		string xs = to_string(x), ys = to_string(y), zs = to_string(z);
		// kui täisosa on null, siis seda välja ei kirjutata
		if (z == 0) {
			zs = "";
		}
		// kui arv on negatiivne, käib miinus täisosa ette
		if (n) {
			zs = '-' + zs;
		}
		// täisosa järele murrujooneks niipalju miinuseid kui on nimetaja pikkus
		for (int i = 0; i < ys.length(); ++i) {
			zs = zs + '-';
		}
		// lugeja ette niipalju tühikuid, et joonduks murrujoone peale
		while (xs.length() < zs.length()) {
			xs = ' ' + xs;
		}
		// nimetaja ette niipalju tühikuid, et joonduks murrujoone alla
		while (ys.length() < zs.length()) {
			ys = ' ' + ys;
		}
		val << xs << '\n' << zs << '\n' << ys << '\n';
	}

	return 0;
}
