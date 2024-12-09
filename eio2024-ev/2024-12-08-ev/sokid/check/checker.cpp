#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
#include <cstdlib>
using namespace std;

#define done(r, m) (cout << r << '\n', cerr << m << '\n', exit(0))

int cat(unsigned char c) {
	if (c == 0 or isspace(c)) return 0;
	if (isdigit(c)) return 1;
	if (c == '-') return 2;
	return -1;
}

vector<string> tokenize(istream & is) {
	vector<string> res;
	string tok;
	int last_cat = 0;
	is >> noskipws;
	for (char c; is >> c; ) {
		if (cat(c) != last_cat) {
			if (!tok.empty()) {
				res.push_back(tok);
				tok = "";
			}
			last_cat = cat(c);
		}
		if (cat(c) != 0) {
			tok.push_back(c);
		}
	}
	if (!tok.empty()) {
		res.push_back(tok);
	}
	return res;
}

int main(int argc, const char *argv[]) {
	if (argc != 4) {
		done(0, "Usage: " << argv[0] << " input hint output");
	}

	//ifstream in(argv[1]);
	ifstream hint(argv[2]);
	ifstream out(argv[3]);

	auto cor = tokenize(hint);

	auto ans = tokenize(out);

	int i = 0;
	for (const auto & a : ans) {
		if (i < cor.size() and a == cor[i]) {
			++i;
		}
	}

	if (i == cor.size() and ans.size() == cor.size()) {
		done(1, "OK");
	} else if (i == cor.size()) {
		done(0, "Please only output the answer and nothing else; see https://eio.ee/KKK/StdIO for more details");
	} else {
		done(0, "Wrong answer");
	}
}
