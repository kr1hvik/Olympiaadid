#include <iostream>
#include <string>
#include <map>
using namespace std;

int main() {
	int n;
	cin >> n;

	map<string, int> sokid;
	for (int i = 1; i <= n; ++i) {
		string varv;
		cin >> varv;
		// kui seda värvi pole enne nähtud, siis
		// on sokid[varv] algväärtuseks 0
		sokid[varv] += 1;
	}

	int yksi = 0;
	for (auto [varv, arv] : sokid){
		if (arv % 2 > 0){
			yksi += 1;
		}
	}

	if (yksi % 2 > 0){
		cout << -1 << '\n';
	} else{
		cout << yksi / 2 << '\n';
	}
}
