// vaatab läbi kõik arvud soovitud numbrite miinimumist maksimumini;
// kontrollib igaühe kohta, kas see on soovitute hulgas

// hoiab soovide nimekirja hulgana, kus elemendi olemasolu kontroll
// on efektiivne ja seetõttu töötab kiiesti ka suuremates testides

// C++ standardteegis on kaks hulgatüüpi, neist set hoiab oma elemente
// järjestatuna ja unordered_set paisktabelis; siin lahenduses kasutame
// esimest neist kahest hulgatüübist; siis saame minimaalse ja maksimaalse
// soovitud numbritest leida kui hulga esimese ja viimase elemendi

#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main() {
	int n;
	cin >> n;
	set<int> soovid;
	for (int i = 0; i < n; ++i) {
		int soov;
		cin >> soov;
		soovid.insert(soov);
	}

	// kasutame ära, et set on järjestatud
	const int min_soov = *soovid.begin();
	const int max_soov = *soovid.rbegin();

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
