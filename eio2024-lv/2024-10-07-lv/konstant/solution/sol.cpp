#ifdef EVAL
  #include "secret_int.h"
#else
  #include "../att/secret_int.h"
#endif
#include <tuple>
#include <vector>
//#include <iostream>

// 0 -> 0, 1 -> 0xffffffff
secret_int bit_broadcast(secret_int a) {
	return -a;
}
// ternary operator
secret_int select(secret_int cond, secret_int t, secret_int f) {
	return (cond & t) | (~cond & f);
}

secret_int ith_element(std::vector<secret_int> A, secret_int i) {
	secret_int res = 0;
	for(int j = 0; j < A.size(); j++) {
		res ^= bit_broadcast(i == j) & A[j];
	}
	return res;
}

// compare and order 2 elements
void cmp_sort(secret_int& a, secret_int& b) {
	secret_int a_lt_b = bit_broadcast(a < b);
	secret_int min = select(a_lt_b, a, b);
	secret_int max = select(a_lt_b, b, a);
	a = min;
	b = max;
}

void sort_arr(std::vector<secret_int>& A) {
	// https://en.wikipedia.org/wiki/Batcher_odd%E2%80%93even_mergesort
	int n = A.size();
	for(int p = 0; 1<<p < n; p++) {
		for(int k = p; k >= 0; k--) {
			int K = 1<<k;
			for(int j = (k == p ? 0 : K); j < n-K; j += 2*K) {
				for(int i = 0; i < K && i < n-j-K; i++) {
					if((i+j) >> (1+p) == (i+j+K) >> (1+p)) {
						cmp_sort(A[i+j], A[i+j+K]);
					}
				}
			}
		}
	}
}

secret_int connected_components(std::vector<std::vector<secret_int>> A) {
	std::size_t n = A.size();
	std::vector<secret_int> components;
	for(std::size_t i = 0; i < n; i++) components.push_back(i);

	secret_int num_components = n;
	for(std::size_t i = 0; i < n; i++) {
		for(std::size_t j = i + 1; j < n; j++) {
			secret_int do_conn = A[i][j];
			num_components -= do_conn * (components[i] != components[j]);
			// replace all instances of components[i] with components[j]
			secret_int from = components[i];
			secret_int delta = do_conn * (components[j] - components[i]);
			for(std::size_t k = 0; k < n; k++) {
				components[k] += (components[k] == from) * delta;
			}
		}
	}

	return num_components;
}


std::tuple<secret_int, secret_int, std::vector<secret_int>> graph_path(std::vector<std::vector<secret_int>> A, secret_int start, secret_int end) {
	int n = A.size();
	std::vector<secret_int> distances(n, 0xffffffff);
	std::vector<secret_int> parents(n, 0);
	std::vector<secret_int> path_lengths(n, 1);
	// build the path backwards, so we start at the end
	for(int i = 0; i < n; i++) {
		distances[i] = (i != end) * 0xffffffff;
	}
	for(int k = 0; k < n; k++) {
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				// can we get to i by going through j?

				// is there an edge i->j?
				secret_int is_better = (A[i][j] != 0);
				// can we get to j?
				is_better &= (distances[j] < 0xffffffff);
				// is using this edge better?
				secret_int new_distance = A[i][j] + distances[j];
				secret_int old_distance = distances[i];
				is_better &= (new_distance < old_distance);

				is_better = bit_broadcast(is_better);
				distances[i] = select(is_better, new_distance, old_distance);
				parents[i] = select(is_better, j, parents[i]);
				path_lengths[i] = select(is_better, path_lengths[j]+1, path_lengths[i]);
			}
		}
	}

	// find answer
	secret_int distance = ith_element(distances, start);
	secret_int path_len = ith_element(path_lengths, start);

	// reconstruct path
	std::vector<secret_int> path;
	path.push_back(start);
	secret_int current_node = start;
	for(int i = 0; i < n; i++) {
		current_node = ith_element(parents, current_node);
		path.push_back(current_node);
	}

	return std::make_tuple(distance, path_len, path);
}

/********************
* prime check stuff *
********************/

secret_int ctz(secret_int x) {
	// based on https://graphics.stanford.edu/~seander/bithacks.html#ZerosOnRightParallel
	secret_int c = 32;
	secret_int v = x & (-x);
	c -= (v != 0);
	c -= ((v & 0x0000ffff) != 0) << 4;
	c -= ((v & 0x00ff00ff) != 0) << 3;
	c -= ((v & 0x0f0f0f0f) != 0) << 2;
	c -= ((v & 0x33333333) != 0) << 1;
	c -= ((v & 0x55555555) != 0);
	return c;
}
// you can either implement modmul like this,
// or you can use * and implement long division by hand.
// i think both end up being ~equivalent in difficulty.
// (actually, i think the latter is harder because you need to deal with double-width products.)
secret_int modmul(secret_int a, secret_int b, secret_int mod) {
	secret_int res = 0;
	for(int i = 0; i < 32; i++) {
		// if b & 1: res = (res + a) % mod
		// the % is implemented by checking whether the addition would overflow,
		// and subtracting mod if so
		res += (b & 1) * (a - (res >= mod - a)*mod);
		b >>= 1;
		// basically do a <<= 1, a %= mod
		a = a + a - (a > mod - a)*mod;
	}
	return res;
}
secret_int modpow(secret_int base, secret_int exp, secret_int mod) {
	secret_int res = 1;
	for(int i = 0; i < 32; i++) {
		res = select(bit_broadcast(exp & 1), modmul(res, base, mod), res);
		// väga marginally kiiremad:
		// res += (exp & 1) * (modmul(res, base, mod) - res);
		// res = modmul(res, (exp & 1) * (base - 1) + 1, mod);
		exp >>= 1;
		base = modmul(base, base, mod);
	}
	return res;
}

secret_int miller_rabin_trial(secret_int n, secret_int s, secret_int a) {
	// haha barrel shifter go brrrrrr
	secret_int d = (n - 1) >> s;
	secret_int x = modpow(a, d, n);
	secret_int is_prime = 1;
	for(int i = 0; i < 32;) {
		secret_int y = modmul(x, x, n);
		// if(y == 1 and x != 1 and x != n-1): composite
		// also need to check that we "should" do this loop iteration
		is_prime &=	1-((i < s) & (y == 1) & (x != 1) & (x != n-1));
		x = y;
		i++;
		// final loop iter: if(y != 1) composite
		is_prime &= 1-((i == s) & (y != 1));
	}
	return is_prime;
}

secret_int is_prime(secret_int n) {
	// based on https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test#Testing_against_small_sets_of_bases
	secret_int s = ctz(n - 1);
	secret_int res = (n & 1);
	res &= miller_rabin_trial(n, s, 2);
	// the modular arithmetic stuff breaks when a >= n,
	// but for small n checking a=2 is enough anyways
	res &= (n <= 7) | miller_rabin_trial(n, s, 7);
	res &= (n <= 61) | miller_rabin_trial(n, s, 61);
	return res | (n == 2);
}
