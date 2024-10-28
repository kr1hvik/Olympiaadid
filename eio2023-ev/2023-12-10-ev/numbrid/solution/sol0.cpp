// vaatab läbi kõik arvud soovitud numbrite miinimumist maksimumini;
// kontrollib igaühe kohta, kas see on soovitute hulgas

// hoiab soovide nimekirja loendina, kus elemendi olemasolu kontroll
// vajab loendi läbivaatamist, milleks kulub kuni N sammu;
// kõigi võimalike väärtuste kontrolliks kulub seega (max-min)*N sammu,
// mis jääb suuremate andmemahtude korral liiga aeglaseks

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	int n;
	cin >> n;
	vector<int> soovid;
	for (int i = 0; i < n; ++i) {
		int soov;
		cin >> soov;
		soovid.push_back(soov);
	}

	vector<int> vastus;
	const int min_soov = *min_element(soovid.begin(), soovid.end());
	const int max_soov = *max_element(soovid.begin(), soovid.end());
	for (int number = min_soov; number < max_soov; ++number) {
		if (find(soovid.begin(), soovid.end(), number) == soovid.end()) {
			vastus.push_back(number);
		}
	}

	cout << vastus.size() << '\n';
	for (auto number : vastus) {
		cout << number << ' ';
	}
	cout << '\n';
}
