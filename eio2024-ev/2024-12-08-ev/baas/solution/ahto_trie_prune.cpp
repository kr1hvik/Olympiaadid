// optimaalne lahendus trie põhjal
// ehitab trie ainult sisendi esimese rea kohta
// teiste ridade kohta loeb ainult, millistele elementidele vastavad prefiksid neis ka esinevad
// teenib täispunktid

#include <iostream>
#include <string>
#include <map>
using namespace std;

struct Node {
	int row = 0;
	map<char, Node> next;
} root;

void add_word(int row, const string & word) {
	Node *curr = &root;
	for (auto c : word) {
		if (row > 1 and not curr->next.contains(c)) {
			return;
		}
		curr = &curr->next[c];
		if (curr->row == row - 1) {
			curr->row = row;
		}
	}
}

string best;

void find_best(const Node & curr = root, string word = "") {
	if (curr.row < root.row) {
		return;
	}
	if (best.length() < word.length()) {
		best = word;
	}
	for (const auto & [c, next] : curr.next) {
		find_best(next, word + c);
	}
}

int main() {
	int m, n;
	cin >> m >> n;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			string word;
			cin >> word;
			add_word(1 + i, word);
		}
	}
	root.row = n;
	find_best();
	cout << best << '\n';
}
