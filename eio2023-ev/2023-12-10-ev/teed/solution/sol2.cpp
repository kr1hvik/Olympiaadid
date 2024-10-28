#include <iostream>
using namespace std;

int main() {
	int arv1, arv2, arv3;
	cin >> arv1 >> arv2 >> arv3;

	if ((arv1 == 1 or arv1 == 3) and
			(arv2 == 6 or arv2 == 8) and
			(arv3 == 2 or arv3 == 5)) {
		cout << "JAH\n";
	} else {
		cout << "EI\n";
	}
}
