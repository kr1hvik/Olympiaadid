#include <iostream>
using namespace std;

int main() {
	// loeme praeguse kellaaja
	int H, M;
	cin >> H >> M;

	// loeme peatuste arvu
	int N;
	cin >> N;

	// loeme peatuste andmed
	for (int i = 1; i <= N; ++i) {
		int H, M, J;
		cin >> H >> M >> J;
		// TODO: kasutame või salvestame peatuse i andmed
	}

	// TODO: leiame vastuse
	bool jouab = true;
	int peatus = 0;

	// väljastame vastuse
	if (jouab) {
		cout << "JAH" << '\n';
		cout << peatus << '\n';
	} else {
		cout << "EI" << '\n';
		cout << peatus << '\n';
	}
}
