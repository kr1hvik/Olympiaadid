// naiivne O(N^2) keerukusega lahendus; jääb suuremates testides ajahätta

// erinevuse arvutamine täpselt ülesande püstituse järgi 
// alternatiivina võiks std::max(a[i],a[j])-std::min(a[i],a[j])
// asemel kirjutada ka std::abs(a[i]-a[j])

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

	long long s = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < i; ++j) {
			s += std::max(a[i], a[j]) - std::min(a[i], a[j]);
		}
	}

	std::cout << s << '\n';
}
