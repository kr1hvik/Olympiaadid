#include <cstdint>

using u32 = std::uint32_t;
extern std::size_t total_op_count;

class secret_int {
private:
	std::uint64_t masked_value;
	// implemented in grader.cpp
	static u32 unmask(std::uint64_t);
	static std::uint64_t mask(std::uint32_t);
	u32 value() const { return unmask(masked_value); }
	friend int main();

public:
	secret_int(u32 value_in) : masked_value(mask(value_in)) {}

#define DO_OP(op) \
	friend secret_int operator op (const secret_int& a, const secret_int& b) { total_op_count += 1; return secret_int(a.value() op b.value()); } \
	friend secret_int operator op (u32 a, const secret_int& b) { total_op_count += 1; return secret_int(a op b.value()); } \
	friend secret_int operator op (const secret_int& a, u32 b) { total_op_count += 1; return secret_int(a.value() op b); }

#define DO_ASSIGN_OP(op, opeq) \
	DO_OP(op) \
	secret_int& operator opeq (u32 other) { total_op_count += 1; return *this = secret_int(value() op other); } \
	secret_int& operator opeq (const secret_int& other) { total_op_count += 1; return *this = secret_int(value() op other.value()); }

	DO_ASSIGN_OP(+, +=)
	DO_ASSIGN_OP(-, -=)
	DO_ASSIGN_OP(*, *=)
	DO_ASSIGN_OP(^, ^=)
	DO_ASSIGN_OP(&, &=)
	DO_ASSIGN_OP(|, |=)
	DO_ASSIGN_OP(>>, >>=)
	DO_ASSIGN_OP(<<, <<=)
	DO_OP(==)
	DO_OP(!=)
	DO_OP(>)
	DO_OP(<)
	DO_OP(>=)
	DO_OP(<=)
	secret_int operator-() const { total_op_count += 1; return secret_int(-value()); }
	secret_int operator~() const { total_op_count += 1; return secret_int(~value()); }
};

