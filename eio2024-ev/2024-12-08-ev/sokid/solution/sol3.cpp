#include <iostream>
#include <string>
#include <set>
using namespace std;

int main() {
	int n;
	cin >> n;

	set<string> yksikud;
	for (int i = 1; i <= n; ++i) {
		string varv;
		cin >> varv;
		if (yksikud.contains(varv)) {
			yksikud.erase(varv);
		} else {
			yksikud.insert(varv);
		}
	}

	if (n % 2 > 0){
		cout << -1 << '\n';
	} else{
		cout << yksikud.size() / 2 << '\n';
	}
}
