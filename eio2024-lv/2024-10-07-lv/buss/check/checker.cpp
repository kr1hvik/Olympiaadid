#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
#include <cmath>
#include <cstdlib>
using namespace std;

#define done(r, m) (cout << r << '\n', cerr << m << '\n', exit(0))

int cat(unsigned char c) {
	if (c == 0 or isspace(c)) return 0;
	if (isdigit(c)) return 1;
	return 3;
}

vector<string> tokenize(istream & is) {
	vector<string> res;
	string tok;
	int last_cat = -1;
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

	// input file not used
	ifstream hint(argv[2]);
	ifstream out(argv[3]);

	string h[2];
	hint >> h[0] >> h[1];

	auto ans = tokenize(out);
	int i = 0;
	for (const auto & a : ans) {
		if (i < 2 and a == h[i]) {
			++i;
		}
	}

	if (i == 2 and ans.size() == 2) {
		done(1, "OK");
	} else if (i == 2) {
		done(0, "Presentation error, see https://eio.ee/KKK/StdIO");
	} else {
		done(0, "Wrong answer");
	}
}
