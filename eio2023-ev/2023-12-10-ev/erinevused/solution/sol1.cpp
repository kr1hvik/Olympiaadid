// efektiivne lahendus: sorteerimine on O(N*log(N)), ülejäänu O(N)

// põhineb tähelepanekul, et iga a[i] esineb lõppsummas plussmärgiga
// nii palju kordi, kui palju on selliseid a[j], mis on temast väiksemad,
// ja miinusmärgiga nii palju kordi, kui palju on temast suuremaid a[j]

// a[] sorteerimise järel on elemendist a[i] väiksemad temast vasakul
// ja suuremad temast paremal

// igast omavahel võrdsete elementide paarist läheb üks summasse pluss-
// ja teine miinusmärgiga, mis annab ka õige tulemuse

#include <iostream>
#include <vector>
#include <algorithm>

int main() {
	int n;
	std::cin >> n;
	std::vector<int> a(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> a[i];
	}

	std::sort(a.begin(), a.end());

	long long s = 0;
	for (int i = 0; i < n; ++i) {
		s += a[i] * i;
		s -= a[i] * (n - 1 - i);
	}

	std::cout << s << '\n';
}
