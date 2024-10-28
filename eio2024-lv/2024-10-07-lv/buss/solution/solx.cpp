// laiendatud lahendus; kontrollib lisaks, kas vastus on ühene

#include <iostream>
using namespace std;

int main() {
	// loeme sisendist praeguse kellaaja ning teisendame selle minutiteks
	int H, M;
	cin >> H >> M;
	const int C = H * 60 + M;

	int ajavaru = -10001; // muutuja maksimaalse ajavaru jaoks
	int peatus = -1; // muutuja seni suurima ajavaruga peatuse meeles pidamiseks
	int kordus = 0;

	int N;
	cin >> N;
	for (int i = 1; i <= N; ++i) {
		int J;
		cin >> H >> M >> J;
		const int B = H * 60 + M; // teisendame bussi saabumisaja minutiteks
		const int varu = (B - C) - J; // arvutame, mitu minutit varem jõuab Juku
		if (varu > ajavaru) { // kui leidsime parema ajavaru, siis uuendame
			ajavaru = varu;
			peatus = i;
			kordus = 0;
		}
		if (varu == ajavaru) { // kui leidsime uue sama hea ajavaru, siis loendame
			kordus += 1;
		}
	}
	// väljund
	if (ajavaru >= 0) {
		cout << "JAH\n";
	} else {
		cout << "EI\n";
	}
	cout << peatus << '\n';
	// lisainfo
	if (ajavaru == 0) {
		cerr << "Piirjuht\n";
	}
	if (kordus == 1) {
		cerr << "Vastus on ühene\n";
	} else {
		cerr << "Vastus pole ühene\n";
	}
}
