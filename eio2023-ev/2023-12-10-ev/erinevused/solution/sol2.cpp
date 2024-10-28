// efektiivne lahendus: O(N + maxA^2)

// loendab iga võimaliku tulemuse esinemiste arvu sisendis;
// siis vaatab kõiki võimalike tulemuste paare ja liidab
// iga paari elementide vahe summasse nii mitme kordselt,
// kui mitu sellist tulemuste paari sisendi elementidest
// moodustada saab

#include <iostream>
#include <vector>

const int piir = 1001; // tulemuste ülempiir

int main() {
	int n;
	std::cin >> n;
	std::vector<int> a(n);
	for (auto & t : a) {
		std::cin >> t;
	}

	std::vector<int> mitu(piir);
	for (auto t : a) {
		mitu[t] += 1;
	}

	long long s = 0;
	for (int t = 0; t < piir; ++t) {
		for (int u = 0; u < t; ++u) {
			s += (long long) (t - u) * mitu[t] * mitu[u];
		}
	}

	std::cout << s << '\n';
}
