#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

#define done(r, m) (cout << r << '\n', cerr << m << '\n', exit(0))

int cat(unsigned char c) {
	if (c == 0 or isspace(c)) return 0;
	if (c == '-' or isdigit(c)) return 1;
	if (isalpha(c)) return 2;
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

vector<string> toupper(const vector<string> & vs) {
	vector<string> res = vs;
	for (auto & s : res) {
		for (auto & c : s) {
			c = toupper(c);
		}
	}
	return res;
}

int main(int argc, char const *argv[]) {
	if(argc != 4) {
		done(0, "Usage: " << argv[0] << " input hint output");
	}

	// input file not used
	ifstream hint(argv[2]);
	ifstream out(argv[3]);

	string correct;
	hint >> correct;

	auto answer = tokenize(out);
	auto upper = toupper(answer);

	if (answer.size() == 1 and answer[0] == correct) {
		done(1, "OK");
	}
	if (upper.size() == 1 and upper[0] == correct) {
		done(0, "Please output the answer in UPPERCASE");
	}
	for (auto const & a : answer) {
		if (a == correct) {
			done(0, "Please only output the answer and NOTHING ELSE");
		}
	}
	for (auto const & a : upper) {
		if (a == correct) {
			done(0, "Please only output the answer in UPPERCASE and NOTHING ELSE");
		}
	}
	done(0, "Wrong answer");
}
