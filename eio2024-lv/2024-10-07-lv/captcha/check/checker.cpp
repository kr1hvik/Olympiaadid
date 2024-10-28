#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <cstdlib>
using namespace std;

#define done(r, m) (cout << r << '\n', cerr << m << '\n', exit(0))

vector<string> pics(5);
map<string, int> clicks;
const int none = -1;

void click(const string & s) {
	const int t = clicks[s];
	if (t == none) {
		int m = none;
		for (const auto & [p, i] : clicks) {
			if (m < i) m = i;
		}
		clicks[s] = m + 1;
	} else {
		clicks[s] = none;
		for (auto & [p, i] : clicks) {
			if (i > t) i -= 1;
		}
	}
}

int main(int argc, const char *argv[]) {
	if (argc != 4) {
		done(0, "Usage: " << argv[0] << " input hint output");
	}

	ifstream in(argv[1]);
	ifstream hint(argv[2]);
	ifstream out(argv[3]);

	for (auto & s : pics) {
		in >> s;
		clicks[s] = none;
	}
	int n;
	in >> n;
	for (int i = 0; i < n; ++i) {
		string s;
		in >> s;
		click(s);
	}

	int h_m;
	hint >> h_m;

	int m;
	out >> m;
	if (!out or m < 0) {
		done(0, "Invalid M (must be non-negative integer)");
	}
	for (int i = 0; i < m; ++i) {
		string s;
		out >> s;
		if (!out) {
			done(0, "Number of output lines does not match M");
		}
		if (!clicks.count(s)) {
			done(0, "Unknown picture name in output");
		}
		click(s);
	}
	string s;
	out >> s;
	if (out) {
		done(0, "Number of output lines does not match M");
	}

	for (int i = 0; i < pics.size(); ++i) {
		if (clicks[pics[i]] != i) {
			done(0, "Captcha not solved correctly");
		}
	}
	if (m > h_m) {
		done(0, "Too many clicks used");
	}
	done(1, "OK");
}
