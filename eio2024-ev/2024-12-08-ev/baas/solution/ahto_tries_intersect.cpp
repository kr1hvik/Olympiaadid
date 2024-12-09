// asümptootiliselt optimaalne lahendus trie põhjal
// ehitab trie iga rea kohta eraldi ja siis võtab neist ühisosa
// hoiab korraga mälus ainult senist ühisosa ja jooksva rea trie'd

#include <iostream>
#include <string>
#include <map>
using namespace std;

struct Node {
	map<char, Node> next;
};

void add_word(Node & root, const string & word) {
	Node *curr = &root;
	for (auto c : word) {
		// next[c] poole pöördumine lisab uue elemendi,
		// kui seda veel olemas ei ole
		curr = &curr->next[c];
	}
}

Node intersect(Node & a, Node & b) {
	Node res;
	for (auto & [c, _] : a.next) {
		if (b.next.contains(c)) {
			res.next[c] = intersect(a.next[c], b.next[c]);
		}
	}
	return res;
}

string best;

void find_best(const Node & curr, string word = "") {
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

	Node file_trie;
	for (int i = 0; i < n; ++i) {
		Node line_trie;
		for (int j = 0; j < m; ++j) {
			string word;
			cin >> word;
			add_word(line_trie, word);
		}
		if (i == 0) {
			file_trie = line_trie;
		} else {
			file_trie = intersect(file_trie, line_trie);
		}
	}
	find_best(file_trie);
	cout << best << '\n';
}
