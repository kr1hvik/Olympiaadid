// vaatab läbi kõik arvud soovitud numbrite miinimumist maksimumini;
// kontrollib igaühe kohta, kas see on soovitute hulgas

// hoiab soovide nimekirja hulgana, kus elemendi olemasolu kontroll
// on efektiivne ja seetõttu töötab kiiesti ka suuremates testides

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

	vector<int> vastus;
	const int min_soov = *min_element(soovid.begin(), soovid.end());
	const int max_soov = *max_element(soovid.begin(), soovid.end());
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