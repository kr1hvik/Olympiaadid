#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <cstring>

void done(double n, const char *s, ...) {
	fprintf(stdout, "%lf\n", n);
	va_list ap;
	va_start(ap, s);
	vfprintf(stderr, s, ap);
	va_end(ap);
	fprintf(stderr, "\n");
	exit(0);
}

char *strip(char *s) {
	for (int i = 0; s[i] != 0; ++i) {
		if (s[i] == '\n' || s[i] == '\r') {
			s[i] = 0;
		}
	}
	return s;
}

char s1[100], s2[100];
int n1, n2;

int main(int argc, const char *argv[]) {
	if (argc != 4) {
		done(0, "Usage: %s input hint output", argv[0]);
	}

	// don't need the input file

	FILE *hint = fopen(argv[2], "rt");
	if (!hint) {
		done(0, "Can't open hint file %s", argv[2]);
	}
	FILE *out = fopen(argv[3], "rt");
	if (!out) {
		done(0, "Can't open output file %s", argv[3]);
	}

	while (fgets(s1, sizeof(s1), hint)) {
		if (fgets(s2, sizeof(s2), out)) {
			if (strcmp(strip(s1), strip(s2)) == 0 && n1 == n2) {
				++n2;
			}
		}
		++n1;
	}
	if (fscanf(out, "%10s", s2) > 0) {
		done(0.0, "Format error");
	}
	if (n1 == n2) {
		done(1.0, "OK");
	}
	if (n2 >= 2) {
		done(0.5, "Partial score");
	}
	done(0.0, "Wrong answer");
}
