#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
using namespace std;

#define done(r, m) (cout << r << '\n', cerr << m << '\n', exit(0))

int main(int argc, const char *argv[]) {
	if (argc != 4) {
		done(0, "Usage: " << argv[0] << " input hint output");
	}

	// input file not used
	ifstream hint(argv[2]);
	ifstream out(argv[3]);

	int m_hint;
	hint >> m_hint;
	vector<int> a_hint(m_hint);
	for (auto & a : a_hint) {
		hint >> a;
	}

	int m_out;
	out >> m_out;
	if (!out) done(0, "Invalid M");
	if (m_out != m_hint) done(0, "Wrong M");

	vector<int> a_out(m_out);
	for (auto & a : a_out) {
		out >> a;
		if (!out) done(0, "Invalid list (not M integers)");
	}
	char c;
	if (out >> c) done(0, "Invalid list (not M integers)");

	for (int i = 1; i < m_out; ++i) {
		if (a_out[i - 1] >= a_out[i]) done(0, "List not sorted");
	}
	if (a_out != a_hint) done(0, "Wrong list");

	done(1, "OK");
}
