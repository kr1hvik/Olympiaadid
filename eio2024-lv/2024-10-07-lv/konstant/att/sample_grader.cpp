#include <iostream>
#include <vector>
#include <tuple>
#include "secret_int.h"

// task function declarations
secret_int ith_element(std::vector<secret_int> A, secret_int i);
void sort_arr(std::vector<secret_int>& A);
secret_int connected_components(std::vector<std::vector<secret_int>> A);
// result is (distance, path_length, path)
std::tuple<secret_int, secret_int, std::vector<secret_int>> graph_path(std::vector<std::vector<secret_int>> A, secret_int B, secret_int C);
secret_int is_prime(secret_int N);

// wrappers for task functions that do I/O
void test_ith_element() {
	u32 i, n;
	std::cin >> n >> i;
	secret_int si = secret_int(i);
	std::vector<secret_int> a;
	for (u32 j = 0; j < n; j++) {
		u32 temp;
		std::cin >> temp;
		a.push_back(secret_int(temp));
	}
	secret_int out = ith_element(a, si);
	std::cout << out.DEBUG_get_value() << std::endl;
}
void test_sort() {
	u32 n;
	std::cin >> n;
	std::vector<secret_int> a;
	for (u32 j = 0; j < n; j++) {
		u32 temp;
		std::cin >> temp;
		a.push_back(secret_int(temp));
	}
	sort_arr(a);
	for (secret_int value : a) {
		std::cout << value.DEBUG_get_value() << ' ';
	}
	std::cout << std::endl;
}
void test_connected_components() {
	std::size_t n;
	std::cin >> n;
	std::vector<std::vector<secret_int>> A(n);
	for (std::size_t i = 0; i < n; i++) {
		for (std::size_t j = 0; j < n; j++) {
			u32 tmp;
			std::cin >> tmp;
			A[i].push_back(tmp);
		}
	}
	secret_int out = connected_components(std::move(A));
	std::cout << out.DEBUG_get_value() << std::endl;
}
void test_graph_path() {
	std::size_t n;
	std::cin >> n;
	u32 start, end;
	std::cin >> start >> end;
	std::vector<std::vector<secret_int>> A(n);
	for (std::size_t i = 0; i < n; i++) {
		for (std::size_t j = 0; j < n; j++) {
			u32 tmp;
			std::cin >> tmp;
			A[i].push_back(tmp);
		}
	}
	std::tuple<secret_int, secret_int, std::vector<secret_int>> out = graph_path(std::move(A), start, end);
	u32 distance = std::get<0>(out).DEBUG_get_value();
	u32 path_length = std::get<1>(out).DEBUG_get_value();
	std::vector<secret_int> out_path = std::get<2>(out);
	if (path_length > out_path.size()) {
		std::cerr << "out_path too short\n";
		std::exit(3);
	}
	std::cout << distance << std::endl;
	std::cout << path_length << std::endl;
	for (u32 i = 0; i < path_length; i++) {
		std::cout << out_path[i].DEBUG_get_value() << ' ';
	}
	std::cout << std::endl;
}
void test_prime() {
	u32 n;
	std::cin >> n;
	std::cout << is_prime(n).DEBUG_get_value() << std::endl;
}

int main() {
	std::size_t subtask_num, test_count;
	std::cin >> subtask_num >> test_count;

	for (std::size_t i = 0; i < test_count; i++) {
		if (subtask_num == 0) {
			test_ith_element();
		} else if (subtask_num == 1) {
			test_sort();
		} else if (subtask_num == 2) {
			test_connected_components();
		} else if (subtask_num == 3) {
			test_graph_path();
		} else if (subtask_num == 4) {
			test_prime();
		} else {
			std::cerr << "Unknown subtask.\n";
			return 3;
		}
	}
}
