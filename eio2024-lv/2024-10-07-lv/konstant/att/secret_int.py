import operator
BITS = 2**32 - 1

def op_impl(op):
    def inner(self, b):
        if isinstance(b, secret_int):
            b_val = b.DEBUG_value
        elif isinstance(b, int):
            b_val = b & BITS
        else:
            return NotImplemented
        return secret_int(op(self.DEBUG_value, b_val))
    def inner_refl(self, b):
        if isinstance(b, int):
            return secret_int(op(b & BITS, self.DEBUG_value))
        else:
            return NotImplemented
    return inner, inner_refl

class secret_int:
    def __init__(self, val):
        # this value can be read for local debugging, but it does not exist on the grading server
        self.DEBUG_value = val & BITS
    # most standard integer operations are implemented (but they always return secret_ints)
    __add__, __radd__ = op_impl(operator.__add__)
    __sub__, __rsub__ = op_impl(operator.__sub__)
    __mul__, __rmul__ = op_impl(operator.__mul__)
    # /, // and % are not allowed
    __lshift__, __rlshift__ = op_impl(operator.__lshift__)
    __rshift__, __rrshift__ = op_impl(operator.__rshift__)
    __and__, __rand__ = op_impl(operator.__and__)
    __xor__, __rxor__ = op_impl(operator.__xor__)
    __or__, __ror__ = op_impl(operator.__or__)
    # comparison operators: these return the integer 0 or 1 depending on the comparison result, as a secret_int
    __eq__ = op_impl(operator.__eq__)[0]
    __ne__ = op_impl(operator.__ne__)[0]
    __lt__ = op_impl(operator.__lt__)[0]
    __le__ = op_impl(operator.__le__)[0]
    __gt__ = op_impl(operator.__gt__)[0]
    __ge__ = op_impl(operator.__ge__)[0]
    def __neg__(self):
        return secret_int(-self.DEBUG_value)
    def __invert__(self):
        return secret_int(~self.DEBUG_value)
    def __bool__(self):
        raise TypeError("secret_int cannot be converted to bool!")
