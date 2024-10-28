#ifdef EVAL
  #include "secret_int.h"
#else
  #include "../att/secret_int.h"
#endif
#include <algorithm>
#include <vector>
#include <tuple>
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
	return 0;
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
	// tweak of insertion sort
	for(int i = 1; i < A.size(); i++) {
		for(int j = i; j > 0; j--) {
			cmp_sort(A[j-1], A[j]);
		}
	}
}

secret_int connected_components(std::vector<std::vector<secret_int>> A) {
	return 0;
}


std::tuple<secret_int, secret_int, std::vector<secret_int>> graph_path(std::vector<std::vector<secret_int>> A, secret_int start, secret_int end) {
	std::size_t n = A.size();
	std::vector<std::vector<secret_int>> dist(n, std::vector<secret_int>(n, 0));
	std::vector<std::vector<secret_int>> prev(n, std::vector<secret_int>(n, 0));

	for(std::size_t i = 0; i < n; i++) {
		for(std::size_t j = 0; j < n; j++) {
			secret_int is_edge = bit_broadcast(A[i][j] != 0);
			dist[i][j] = select(is_edge, A[i][j], 0xffffffff);
			prev[i][j] = select(is_edge, i, 0);
		}
	}
	for(std::size_t i = 0; i < n; i++) {
		dist[i][i] = 0;
		prev[i][i] = i;
	}

	for(std::size_t k = 0; k < n; k++) {
		for(std::size_t i = 0; i < n; i++) {
			for(std::size_t j = 0; j < n; j++) {
				secret_int cond = dist[i][j] > dist[i][k] + dist[k][j];
				cond &= dist[i][k] + dist[k][j] > dist[i][k]; // check that addition doesn't overflow
				secret_int improve = bit_broadcast(cond);
				dist[i][j] = select(improve, dist[i][k] + dist[k][j], dist[i][j]);
				prev[i][j] = select(improve, prev[k][j], prev[i][j]);
			}
		}
	}

	// distance is dist[start][end]
	secret_int the_distance = 0;
	for(std::size_t i = 0; i < n; i++) {
		for(std::size_t j = 0; j < n; j++) {
			the_distance |= ((i == start) & (j == end)) * dist[i][j];
		}
	}

	secret_int cur = end;
	std::vector<secret_int> path;
	path.push_back(cur);
	secret_int path_length = 1;
	for(std::size_t k = 1; k < n; k++) {
		secret_int path_member = 0;
		for(std::size_t i = 0; i < n; i++) {
			for(std::size_t j = 0; j < n; j++) {
				secret_int correct = bit_broadcast((i == start) & (j == cur));
				path_member = select(correct, prev[i][j], path_member);
			}
		}
		path.push_back(path_member);
		path_length += (cur != start);
		cur = path_member;
	}

	std::reverse(path.begin(), path.end());
	// the path vector contains `n` elements. we need to shift the first `n-path_length` elements from the beginning to the end.
	// for k in path_length..n:
	//	   // move element 0 to the end
	for(int i = 0; i < n; i++) {
		secret_int correct = bit_broadcast(i >= path_length);
		for(int j = 1; j < n; j++) {
			// swap path[j-1], path[j] if needed
			secret_int temp = path[j-1];
			path[j-1] = select(correct, path[j], path[j-1]);
			path[j] = select(correct, temp, path[j]);
		}
	}

	return std::make_tuple(the_distance, path_length, path);
}

secret_int rem(secret_int a, uint32_t b) {
	// a % b
	secret_int r = 0;
	for(int i = 0; i < 32; i++) {
		r <<= 1;
		r |= (a >> (31-i)) & 1;
		r -= (r >= b) * b;
	}
	return r;
}
bool meta_trial_divide(int i) {
	for(int j = 3; j*j <= i; j++) {
		if(i % j == 0) return false;
	}
	return true;
}
std::vector<int> prime_cache;
secret_int is_prime(secret_int k) {
	if(prime_cache.size() == 0) {
		// going up to 65536 gets TLE
		for(int i = 3; i < 1000; i += 2) {
			if(meta_trial_divide(i)) prime_cache.push_back(i);
		}
	}
	secret_int res = (k & 1) & (k != 1);
	for(int i : prime_cache)
		res &= 1-(i < k & rem(k, i) == 0);
	return res | (k == 2);
}
