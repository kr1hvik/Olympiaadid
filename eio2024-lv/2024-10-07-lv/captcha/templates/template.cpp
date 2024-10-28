#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
	// loeme piltide nõutud järjekorra
	vector<string> pics(5);
	for (auto & s : pics) {
		cin >> s;
	}
	// loeme väikevenna klõpsimise andmed
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		string s;
		cin >> s;
		// TODO: kasutame või salvestame i. klõpsamise andmed
	}

	// TODO: leiame vastuse
	vector<string> vastus;

	// väljastame vastuse
	cout << vastus.size() << '\n';
	for (const auto & s : vastus) {
		cout << s << '\n';
	}
}
