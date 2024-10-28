// sorteerib soovitud numbrite jada ja leiab selles "augud"

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	int n;
	cin >> n;
	vector<int> soovid(n);
	for (auto & soov : soovid) {
		cin >> soov;
	}

	sort(soovid.begin(), soovid.end());

	vector<int> vastus;
	for (int i = 1; i < n; ++i) {
		for (int number = soovid[i - 1] + 1; number < soovid[i]; ++number) {
			vastus.push_back(number);
		}
	}

	cout << vastus.size() << '\n';
	for (auto number : vastus) {
		cout << number << ' ';
	}
	cout << '\n';
}
