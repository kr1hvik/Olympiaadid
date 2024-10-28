#include <cstdint>

using u32 = std::uint32_t;

class secret_int {
private:
	// it's not worth trying to extract this value using any tricks with casts or similar
	// the class layout is different on the grading server
	u32 value;

public:
	// a public value can be converted into a secret one if necessary
	secret_int(u32 value_in) : value(value_in) {}

	// helper for debugging: this function does not exist on the grading server
	u32 DEBUG_get_value() const { return value; }

	// implementation of all forms of all standard integer operations

#define DO_OP(op) \
	friend secret_int operator op (const secret_int& a, const secret_int& b) { return secret_int(a.value op b.value); } \
	friend secret_int operator op (u32 a, const secret_int& b) { return secret_int(a op b.value); } \
	friend secret_int operator op (const secret_int& a, u32 b) { return secret_int(a.value op b); }

#define DO_ASSIGN_OP(op, opeq) \
	DO_OP(op) \
	secret_int& operator opeq (u32 other) { value opeq other; return *this; } \
	secret_int& operator opeq (const secret_int& other) { value opeq other.value; return *this; }

	DO_ASSIGN_OP(+, +=)
	DO_ASSIGN_OP(-, -=)
	DO_ASSIGN_OP(*, *=)
	// % and / are not allowed
	DO_ASSIGN_OP(^, ^=)
	DO_ASSIGN_OP(&, &=)
	DO_ASSIGN_OP(|, |=)
	DO_ASSIGN_OP(>>, >>=)
	DO_ASSIGN_OP(<<, <<=)
	// comparison operators: these return the integer 0 or 1 depending on the comparison result, as a secret_int
	DO_OP(==)
	DO_OP(!=)
	DO_OP(>)
	DO_OP(<)
	DO_OP(>=)
	DO_OP(<=)
	// && and || are not included: just & and | can be used in their place

	// unary operators
	secret_int operator-() const { return secret_int(-value); }
	secret_int operator~() const { return secret_int(~value); }
};
