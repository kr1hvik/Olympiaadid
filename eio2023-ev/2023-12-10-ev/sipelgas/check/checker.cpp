#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

#define done(r, m) (cout << r << '\n', cerr << m << '\n', exit(0))

const int map[][2] = {
	{10,  5}, //  0
	{12, 10}, //  1
	{ 5, 12}, //  2
	{ 1,  8}, //  3
	{21,  1}, //  4
	{ 8, 21}, //  5
	{ 4, 11}, //  6
	{18,  4}, //  7
	{11, 18}, //  8
	{ 7,  2}, //  9
	{15,  7}, // 10
	{ 2, 15}, // 11
	{22, 17}, // 12
	{ 0, 22}, // 13
	{17,  0}, // 14
	{13, 20}, // 15
	{ 9, 13}, // 16
	{20,  9}, // 17
	{16, 23}, // 18
	{ 6, 16}, // 19
	{23,  6}, // 20
	{19, 14}, // 21
	{ 3, 19}, // 22
	{14,  3}  // 23
};

int move(int pos, const string & steps) {
	for (auto step : steps) {
		switch (step) {
			case 'V':
				pos = map[pos][0];
				break;
			case 'P':
				pos = map[pos][1];
				break;
			default:
				done(0, "Invalid move");
		}
	}
	return pos;
}

int main(int argc, const char *argv[]) {
	if (argc != 4) {
		done(0, "Usage: " << argv[0] << " input hint output");
	}

	ifstream in(argv[1]);
	ifstream hint(argv[2]);
	ifstream out(argv[3]);

	int n;
	in >> n;
	string s;
	in >> s;

	int pos = move(0, s);

	out >> n;
	if (!out) done(0, "Invalid answer");

	if (n > 0) {
		out >> s;
		if (!out) done(0, "Invalid answer");
	} else {
		s = "";
	}
	if (s.size() != n) done(0, "Invalid answer");

	char c;
	if (out >> c) done(0, "Invalid answer");

	pos = move(pos, s);
	if (pos != 0 and pos != 1 and pos != 2) done(0, "Wrong answer");

	hint >> n;
	if (s.size() > n) done(0, "Wrong answer");

	done(1, "OK");
}
