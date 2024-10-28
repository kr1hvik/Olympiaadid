#include <iostream>
#include <string>
#include <vector>

const std::vector<int> vasakule = {
	10, 12,  5,  1, 21,  8,
	 4, 18, 11,  7, 15,  2,
	22,  0, 17, 13,  9, 20,
	16,  6, 23, 19,  3, 14
};
const std::vector<int> paremale = {
	 5, 10, 12,  8,  1, 21,
	11,  4, 18,  2,  7, 15,
	17, 22,  0, 20, 13,  9,
	23, 16,  6, 14, 19,  3
};

int liigu(int olek, const std::string & sammud) {
	for (auto samm : sammud) {
		if (samm == 'V') {
			olek = vasakule[olek];
		}
		if (samm == 'P') {
			olek = paremale[olek];
		}
	}
	return olek;
}

const std::vector<std::string> teed = {
	"",
	"V", "P",
	"VV", "VP", "PV", "PP",
	"VVV", "VVP", "VPV", "VPP",
	"PVV", "PVP", "PPV", "PPP"
};

int main() {
	int n;
	std::cin >> n;
	std::string tee;
	std::cin >> tee;

	int olek = liigu(0, tee);
	for (const auto & tee : teed) {
		const int lopp = liigu(olek, tee);
		if (lopp == 0 or lopp == 1 or lopp == 2) {
			std::cout << tee.length() << '\n';
			std::cout << tee << '\n';
			break;
		}
	}
}
