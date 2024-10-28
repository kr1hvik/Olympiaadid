#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	vector<string> pildid(5);
	for (auto & pilt : pildid) {
		cin >> pilt;
	}
	int n;
	cin >> n;
	vector<string> klikid;
	for (int i = 0; i < n; ++i) {
		string pilt;
		cin >> pilt;
		const auto it = find(klikid.begin(), klikid.end(), pilt);
		if (it == klikid.end()) {
			klikid.push_back(pilt);
		} else {
			klikid.erase(it);
		}
	}

	vector<string> logi;
	for (int i = 0; i < pildid.size(); ++i) {
		while (klikid.size() > i and klikid[i] != pildid[i]) {
			logi.push_back(klikid[i]);
			klikid.erase(klikid.begin() + i);
		}
		if (klikid.size() <= i) {
			logi.push_back(pildid[i]);
		}
	}

	cout << logi.size() << '\n';
	for (const auto & pilt : logi) {
		cout << pilt << '\n';
	}
}
