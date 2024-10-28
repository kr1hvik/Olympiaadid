#include <fstream>
#include <iostream>
#include <random>
#include <vector>
#include <tuple>

#include "secret_int.h"

std::size_t total_op_count = 0;
using u64 = std::uint64_t;

// task function declarations
secret_int ith_element(std::vector<secret_int> A, secret_int i);
void sort_arr(std::vector<secret_int>& A);
secret_int connected_components(std::vector<std::vector<secret_int>> A);
// result is (distance, path_length, path)
std::tuple<secret_int, secret_int, std::vector<secret_int>> graph_path(std::vector<std::vector<secret_int>> A, secret_int start, secret_int end);
secret_int is_prime(secret_int n);

/*****************************************
* Implementation details of secret_int.h *
*****************************************/

namespace {

// *Really* minimal PCG32 code / (c) 2014 M.E. O'Neill / pcg-random.org
// Licensed under Apache License 2.0 (NO WARRANTY, etc. see website)
typedef struct {
    uint64_t state;
    uint64_t inc;
} pcg32_random_t;
uint32_t pcg32_random_r(pcg32_random_t* rng) {
    uint64_t oldstate = rng->state;
    // Advance internal state
    rng->state = oldstate * 6364136223846793005ULL + (rng->inc | 1);
    // Calculate output function (XSH RR), uses old state for max ILP
    uint32_t xorshifted = ((oldstate >> 18u) ^ oldstate) >> 27u;
    uint32_t rot = oldstate >> 59u;
    return (xorshifted >> rot) | (xorshifted << ((-rot) & 31));
}

// multiplicative inverse mod 2^64
u64 modinv(u64 a) {
    u64 t = 0, newt = 1;
    // "morally" r = 2^64, but can't represent that properly
    u64 r = 0, newr = a;
    while (newr != 0) {
        // due to euclidean algorithm invariants, 0 < newr < r, so division like
        // this is safe
        u64 quot = 1 + (r - newr) / newr;
        // the "real" value of t goes negative sometimes, but we only ever care
        // about t mod 2^64, so we do not care
        std::tie(t, newt) = std::make_tuple(newt, t - quot * newt);
        std::tie(r, newr) = std::make_tuple(newr, r - quot * newr);
    }
    return t;
}

pcg32_random_t rng;
u64 key_a;
u64 key_b;
u64 key_b_inverse;

void init_keys() {
    std::random_device dev;
    key_a = (u64)dev() << 32 | dev();
    key_b = (u64)dev() << 32 | dev() | 1;
    key_b_inverse = modinv(key_b);
}

// implemented like this because secret_int.h only friends main() - thus main
// creates a lambda that allows other functions in this file to access internals
// of secret_int
// (this creates an "unnecessary" dynamic dispatch every time the grader unwraps
// a value, but each unwrapped value is written to stdout which probably has
// higher overhead anyways)
using grader_magic_t = u32(const secret_int&);
grader_magic_t* grader_magic;

}  // namespace

u64 secret_int::mask(u32 v) {
    u32 noise = pcg32_random_r(&rng);
    u32 masked_v = v ^ noise;
    u64 combined = ((u64)masked_v << 32) ^ noise;
    return (combined ^ key_a) * key_b;
}
u32 secret_int::unmask(u64 v) {
    u64 combined = (v * key_b_inverse) ^ key_a;
    return (u32)((combined >> 32) ^ combined);
}


/********************************
* I/O wrappers for each subtask *
********************************/ 

namespace {
std::ifstream inf;
std::ofstream outf;

void test_ith_element() {
    u32 i, n;
    inf >> n >> i;
    std::vector<secret_int> a;
    for (u32 j = 0; j < n; j++) {
        u32 temp;
        inf >> temp;
        a.push_back(secret_int(temp));
    }
    secret_int out = ith_element(a, secret_int(i));
    outf << grader_magic(out) << '\n';
}
void test_sort() {
    u32 n;
    inf >> n;
    std::vector<secret_int> a;
    for (u32 j = 0; j < n; j++) {
        u32 temp;
        inf >> temp;
        a.push_back(secret_int(temp));
    }
    sort_arr(a);
    for (secret_int value : a) {
        outf << grader_magic(value) << ' ';
    }
    outf << '\n';
}
void test_connected_components() {
	std::size_t n;
	inf >> n;
	std::vector<std::vector<secret_int>> A(n);
	for(std::size_t i = 0; i < n; i++) {
		for(std::size_t j = 0; j < n; j++) {
			u32 tmp;
			inf >> tmp;
			A[i].push_back(tmp);
		}
	}
	secret_int out = connected_components(std::move(A));
	outf << grader_magic(out) << '\n';
}
void test_graph_path() {
	std::size_t n;
	inf >> n;
	u32 start, end;
	inf >> start >> end;
	std::vector<std::vector<secret_int>> A(n);
	for(std::size_t i = 0; i < n; i++) {
		for(std::size_t j = 0; j < n; j++) {
			u32 tmp;
			inf >> tmp;
			A[i].push_back(tmp);
		}
	}
	auto out = graph_path(A, start, end); // i think this copies A but whatever
	u32 out_distance = grader_magic(std::get<0>(out));
	u32 out_path_len = grader_magic(std::get<1>(out));
	std::vector<secret_int> out_path = std::get<2>(out);
	outf << out_distance << '\n';
	outf << out_path_len << '\n';
	for(u32 i = 0; i < out_path_len; i++) {
		outf << grader_magic(out_path.at(i)) << ' ';
	}
	outf << '\n';
}
void test_prime() {
	total_op_count = 0;
	u32 n;
	inf >> n;
	u32 res = grader_magic(is_prime(n));
	if(total_op_count > 1000000) {
		outf << "-1\n";
	} else {
		outf << res << '\n';
	}
}

}  // namespace

int main() {
    grader_magic = [](const secret_int& x) { return x.value(); };
	inf = std::ifstream("eeminkruvirnsis.txt");
	outf = std::ofstream("eeminkruvirnval.txt");
    init_keys();
    std::size_t subtask_num, test_count;
    inf >> subtask_num >> test_count;
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
			return 3; // bad input file
        }
    }
	std::cerr << "Total operations: " << total_op_count << '\n';
}
