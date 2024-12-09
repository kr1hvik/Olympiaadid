#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cmath>
using namespace std;

#define done(r, m) (cout << r << '\n', cerr << m << '\n', exit(0))

int main(int argc, const char *argv[]) {
	if (argc != 4) {
		done(0, "Usage: " << argv[0] << " input hint output");
	}

	//ifstream in(argv[1]);
	ifstream hint(argv[2]);
	ifstream out(argv[3]);

	double a_hint;
	hint >> a_hint;

	string buf;
	for (string s; out >> s; ) {
		buf += ' ';
		buf += s;
	}
	for (auto & c : buf) {
		if (c == ',') c = '.';
	}
	istringstream s_out(buf);

	bool answer = false;
	bool other = false;
	for (;;) {
		double a_out;
		if (s_out >> a_out) {
			if (isnan(a_out) or isinf(a_out)) {
				other = true;
			} else if (fabs(a_out - a_hint) <= 0.005) {
				answer = true;
			} else {
				other = true;
			}
			continue;
		}
		s_out.clear();
		char c;
		if (s_out >> c) {
			other = true;
			continue;
		}
		break;
	}

	if (answer and not other) {
		done(1, "OK");
	} else if (answer) {
		done(0, "Please only output the answer and nothing else; see https://eio.ee/KKK/StdIO for more details");
	} else {
		done(0, "Wrong answer");
	}
}
