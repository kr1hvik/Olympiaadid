// vaatab läbi kõik arvud soovitud numbrite miinimumist maksimumini;
// kontrollib igaühe kohta, kas see on soovitute hulgas

// hoiab soovide nimekirja hulgana, kus elemendi olemasolu kontroll
// on efektiivne ja seetõttu töötab kiiesti ka suuremates testides

// C++ standardteegis on kaks hulgatüüpi, neist set hoiab oma elemente
// järjestatuna ja unordered_set paisktabelis; siin lahenduses kasutame
// teist neist kahest hulgatüübist; siis peame minimaalse ja maksimaalse
// soovitud numbri leidmiseks hulga elemendid läbi vaatama (aga seda on
// vaja teha ainult üks kord); vastukaaluks on unordered_set tüübil
// elementide hulka lisamine ja elemendi hulka kuulumise kontrollid
// natuke kiiremad kui set tüübil

#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

int main() {
	int n;
	cin >> n;
	unordered_set<int> soovid;
	for (int i = 0; i < n; ++i) {
		int soov;
		cin >> soov;
		soovid.insert(soov);
	}

	// unordered_set pole järjestatud, peame kasutama algoritmi
	const int min_soov = *min_element(soovid.begin(), soovid.end());
	const int max_soov = *max_element(soovid.begin(), soovid.end());

	vector<int> vastus;
	for (int number = min_soov; number < max_soov; ++number) {
		if (!soovid.contains(number)) {
			vastus.push_back(number);
		}
	}

	cout << vastus.size() << '\n';
	for (auto number : vastus) {
		cout << number << ' ';
	}
	cout << '\n';
}
