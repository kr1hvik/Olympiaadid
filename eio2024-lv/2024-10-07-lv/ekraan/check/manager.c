#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <signal.h>

#ifdef DEBUG
#define debugprint(...) fprintf(stderr, __VA_ARGS__)
#else
#define debugprint(...)
#endif

int perms[128][5040];
int opos;

void gen(int start, int output, int pos, int mask) {
	if (mask == 0x7f) {
		perms[start][opos] = output;
		opos++;
		return;
	}
	for (int i = 0; i < 7; i++) {
		if (((1 << i) & mask) == 0) {
			gen(start, (((start >> i) & 1) << pos) | output, pos + 1, mask | (1 << i));
		}
	}
}

//     0
//   1   2
//     3
//   4   5
//     6

int symbols[11] = {119,36,93,109,46,107,123,37,127,111,0}; // 0..9, space

unsigned long long encode(int value, int digits, int perm_nr, int invert, int padding, int order, int lr) {
	unsigned long long retvalue = 0;
	int i;
	for (i = 0; i < digits; i++) {
		unsigned long long v = symbols[value % 10];
		v = (invert == 1) ? v ^ 0x7f : v;
		v = perms[v][perm_nr];

		if (order == 0) {
			retvalue = (retvalue << 7) | v;
		} else {
			retvalue = retvalue | (v << (i * 7));
		}

		value = value / 10;
		if (value == 0 && padding == 0) {
			break;
		}
	}
	// add spaces
	for (i++; i < digits; i++) {
		unsigned long long sp = (invert == 1) ? (symbols[10] ^ 0x7f) : symbols[10];
		if (lr == 1) {
			retvalue = (retvalue << 7) | sp;
		} else {
			retvalue = retvalue | (sp << (i * 7));
		}
	}
	return retvalue;
}

int main(int argc, char **argv) {
	// permutation table for 7-bit numbers
	for (int i = 0; i < 128; i++) {
		opos = 0;
		gen(i, 0, 0, 0);
	}

	signal(SIGPIPE, SIG_IGN);
	FILE *to_prg = fopen(argv[2], "w");
	FILE *from_prg = fopen(argv[1], "r");

	int digits;
	assert(scanf("%d", &digits) == 1);
	assert(digits >= 1 && digits <= 9);
	fprintf(to_prg, "%d\n", digits);
#ifdef VERBOSE
	fprintf(stderr, "-> %d digits\n", digits);
#endif

	int mod = 1;
	for (int i = 0; i < digits; i++) {
		mod = mod * 10;
	}

	double score = 0;
	int num_ok = 0;
	int num_subopt = 0;
	int num_wrong = 0;

	int num_tests;
	assert(scanf("%d", &num_tests) == 1);
	assert(num_tests > 0);
	for (int test = 0; test < num_tests; test++) {
		int value, perm_nr, invert, padding, order, lr, optimal;
		assert(scanf("%d %d %d %d %d %d %d", &value, &perm_nr, &invert, &padding, &order, &lr, &optimal) == 7);
		for (int iter = 1; ; iter++) {
			unsigned long long enc = encode(value, digits, perm_nr, invert, padding, order, lr);
			fprintf(to_prg, "%llu\n", enc);
#ifdef VERBOSE
			fprintf(stderr, "-> %llu\n", enc);
#endif
			fflush(to_prg);
			char buf[100];
			if (fgets(buf, sizeof(buf), from_prg) == NULL) {
				debugprint("test %d failed to read from prg, iter %d\n", test, iter);
				num_wrong += 1;
				break;
			}
			if (strncmp("NEXT", buf, 4) == 0) {
				value = (value + 1) % mod;
#ifdef VERBOSE
				fprintf(stderr, " <- NEXT\n");
#endif
				continue;
			}
			int answer = atoi(buf);
#ifdef VERBOSE
			fprintf(stderr, " <- %d\n", answer);
#endif
			if (optimal > iter) { // solution is bluffing
				debugprint("test %d bluf %d > %d\n", test, optimal, iter);
				num_wrong += 1;
				break;
			}
			if (answer == value)  {
				score += (double) optimal / (double) iter;
				debugprint("test %d OK %d / %d\n", test, optimal, iter);
				if (iter == optimal) {
					num_ok += 1;
				} else {
					num_subopt += 1;
                                        debugprint(" !!! SUBOPTIMAL !!! ");
				}
				break;
			}
			debugprint("test %d WRONG %d, %d / %d\n", test, answer, optimal, iter);
			num_wrong += 1;
			break;
		}
	}
	fprintf(to_prg, "-1\n");
	fflush(to_prg);
	printf("%lf\n", score / num_tests);

#ifndef DEBUG
	fprintf(stderr, "%d OK, %d suboptimal, %d wrong, %0.5lf points\n", num_ok, num_subopt, num_wrong, 10 * score / num_tests);
#endif
	return 0;
}
