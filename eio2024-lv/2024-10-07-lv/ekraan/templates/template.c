#include <stdio.h>

int main() {
	// loeme indikaatorite arvu
	int n;
	fscanf(stdin, "%d", &n);

	// lahendame kõik testid
	for (;;) {
		long long code;
		fscanf(stdin, "%lld", &code);

		// kui rohkem teste pole, lõpetame
		if (code == -1) {
			break;
		}

		// TODO: küsime lisainfot, kuni leiame selle testi vastuse
		for (int i = 0; i < 4; ++i) {
			fprintf(stdout, "NEXT\n");
			fflush(stdout);
			fscanf(stdin, "%lld", &code);
		}

		// TODO: väljastame vastuse ja liigume järgmise testi juurde
		fprintf(stdout, "%d\n", 42);
		fflush(stdout);
	}

	return 0; 
}
