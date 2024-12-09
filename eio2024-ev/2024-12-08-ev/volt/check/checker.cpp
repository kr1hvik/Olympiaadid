#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
using namespace std;

#define done(r, m) (cout << r << '\n', cerr << m << '\n', exit(0))

int main(int argc, const char *argv[]) {
	if (argc != 4) {
		done(0, "Usage: " << argv[0] << " input hint output");
	}

	// input file not used
	ifstream hint(argv[2]);
	ifstream out(argv[3]);

	double d_hint;
	hint >> d_hint;

	double d_out;
	out >> d_out;

	if (!out) done(0, "Invalid answer");
	if (isnan(d_out) or isinf(d_out)) done(0, "Invalid answer");
	if (d_out != d_hint) done(0, "Wrong answer");

	char tmp;
	if (out >> tmp) done(0, "Invalid answer");

	done(1, "OK");
}
