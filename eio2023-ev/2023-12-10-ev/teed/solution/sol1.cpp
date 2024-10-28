#include <iostream>
using namespace std;

int main() {
	int arv;

	cin >> arv;
	if (arv != 1 and arv != 3) {
		cout << "EI\n";
		return 0;
	}

	cin >> arv;
	if (arv != 6 and arv != 8) {
		cout << "EI\n";
		return 0;
	}

	cin >> arv;
	if (arv != 2 and arv != 5) {
		cout << "EI\n";
		return 0;
	}

	cout << "JAH\n";
}
