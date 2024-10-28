#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<string> pildid(5); // nõutav piltide järjekord
vector<string> klikid; // tegelik piltide järjekord; ainult numbritega pildid

// klikib antud pildil
void klikk(const string & pilt) {
	const auto it = find(klikid.begin(), klikid.end(), pilt);
	if (it == klikid.end()) {
		// pildil veel ei ole numbrit, lisame nummerdatud nimekirja lõppu
		klikid.push_back(pilt);
	} else {
		// pildil juba on number, uuesti klikkimine eemaldab selle
		klikid.erase(it);
	}
}

int main() {
	// loeme nõutava järjekorra
	for (auto & pilt : pildid) {
		cin >> pilt;
	}
	// loeme ja simuleerime väikevenna klikid
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		string pilt;
		cin >> pilt;
		klikk(pilt);
	}

	// loome Juku klikkide logi
	vector<string> logi;
	int i = 0;
	// kõigepealt eemaldame valed numbrid
	while (i < klikid.size()) {
		if (klikid[i] == pildid[i]) {
			// number i on juba õige pildi juures, liigume järgmisele
			++i;
		} else {
			// number i on vale pildi juures, kustutamiseks peab Juku sellel klikkima
			logi.push_back(klikid[i]);
			klikk(klikid[i]);
		}
	}
	// seejärel lisame kõik, millel veel numbrit pole
	logi.insert(logi.end(), pildid.begin() + i, pildid.end());

	// väljastame vastuse
	cout << logi.size() << '\n';
	for (const auto & pilt : logi) {
		cout << pilt << '\n';
	}
}
