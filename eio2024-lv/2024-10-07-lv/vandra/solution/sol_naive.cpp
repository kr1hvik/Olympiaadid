// korrektne, aga ebaefektiive lahendus: vaatab läbi kõik laudade paarid
// ja kontrollib iga paari kohta, kas need kaks lauda omavahel kattuvad

#include <iostream>
#include <vector>
using namespace std;

struct laud {
	int x1, y1, x2, y2;
};

bool kattuvad(const laud & l1, const laud & l2) {
	if (l1.x1 >= l2.x2) {
		// l1 tervenisti paremal
		return false;
	}
	if (l2.x1 >= l1.x2) {
		// l2 tervenisti paremal
		return false;
	}
	if (l1.y1 >= l2.y2) {
		// l1 tervenisti kõrgemal
		return false;
	}
	if (l2.y1 >= l1.y2) {
		// l2 tervenisti kõrgemal
		return false;
	}
	return true;
}

int main() {
	// loeme laudade andmed
	int n;
	cin >> n;
	vector<laud> lauad(n);
	for (auto & l : lauad) {
		cin >> l.x1 >> l.y1 >> l.x2 >> l.y2;
	}

	// leiame vastuse
	bool vastus = false;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < i; ++j) {
			if (kattuvad(lauad[i], lauad[j])) {
				vastus = true;
			}
		}
	}

	// väljastame vastuse
	if (vastus) {
		cout << "JAH" << '\n';
	} else {
		cout << "EI" << '\n';
	}
}
