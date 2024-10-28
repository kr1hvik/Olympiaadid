def main():
    # try to avoid polluting the global namespace
    # (or making it too easy to access for the solution....)
    global main
    del main

    import secrets
    import operator
    import sys
    counter = secrets.randbits(30)
    KEY_A = secrets.randbits(32)
    BITS = 2**32 - 1
    OPER_COUNTER = 0

    def mask(x):
        nonlocal counter
        counter = (counter + 1234567) & (2**30 - 1)
        return x ^ (counter << 32) ^ KEY_A
    def unmask(v):
        x = v.__masked_val__
        # would like to make this more complicated, but that tends to slow everything down a lot
        return (x ^ KEY_A) & BITS

    def op_impl(op):
        def inner(self, b):
            if isinstance(b, secret_int):
                b_val = unmask(b)
            elif isinstance(b, int):
                b_val = b & BITS
            else:
                return NotImplemented
            nonlocal OPER_COUNTER
            OPER_COUNTER += 1
            return secret_int(op(unmask(self), b_val))
        def inner_refl(self, b):
            nonlocal OPER_COUNTER
            OPER_COUNTER += 1
            if isinstance(b, int):
                return secret_int(op(b & BITS, unmask(self)))
            else:
                return NotImplemented
        return inner, inner_refl

    class secret_int:
        def __init__(self, val):
            self.__masked_val__ = mask(val & BITS)
        __add__, __radd__ = op_impl(operator.__add__)
        __sub__, __rsub__ = op_impl(operator.__sub__)
        __mul__, __rmul__ = op_impl(operator.__mul__)
        __lshift__, __rlshift__ = op_impl(operator.__lshift__)
        __rshift__, __rrshift__ = op_impl(operator.__rshift__)
        __and__, __rand__ = op_impl(operator.__and__)
        __xor__, __rxor__ = op_impl(operator.__xor__)
        __or__, __ror__ = op_impl(operator.__or__)
        __eq__ = op_impl(operator.__eq__)[0]
        __ne__ = op_impl(operator.__ne__)[0]
        __lt__ = op_impl(operator.__lt__)[0]
        __le__ = op_impl(operator.__le__)[0]
        __gt__ = op_impl(operator.__gt__)[0]
        __ge__ = op_impl(operator.__ge__)[0]
        def __neg__(self):
            nonlocal OPER_COUNTER
            OPER_COUNTER += 1
            return secret_int(-unmask(self))
        def __invert__(self):
            nonlocal OPER_COUNTER
            OPER_COUNTER += 1
            return secret_int(~unmask(self))
        def __bool__(self):
            raise Exception('converting secret_int to bool')

    class secret_int_module:
        def __init__(self):
            self.secret_int = secret_int
    sys.modules['secret_int'] = secret_int_module()

    in_file = open("eeminkruvirnsis.txt")
    out_file = open("eeminkruvirnval.txt", 'w')

    import konstant

    def test_ith_element():
        _n, i = map(int, in_file.readline().split())
        i = secret_int(i)
        a = [secret_int(int(x)) for x in in_file.readline().split()]
        res = konstant.ith_element(a, i)
        print(unmask(res), file=out_file)

    def test_sort():
        _n = in_file.readline()
        a = [secret_int(int(x)) for x in in_file.readline().split()]
        konstant.sort_arr(a)
        print(*[unmask(x) for x in a], file=out_file)

    def test_connected_components():
        n = int(in_file.readline())
        A = []
        for _ in range(n):
            A.append([secret_int(int(x)) for x in in_file.readline().split()])
        res = konstant.connected_components(A)
        print(unmask(res), file=out_file)

    def test_graph_path():
        n, start, end = map(int, in_file.readline().split())
        start, end = map(secret_int, [start, end])
        A = []
        for _ in range(n):
            A.append([secret_int(int(x)) for x in in_file.readline().split()])
        res = konstant.graph_path(A, start, end)
        (distance, path_len, path) = res
        print(unmask(distance), file=out_file)
        path_len = unmask(path_len)
        assert path_len <= len(path)
        print(path_len, file=out_file)
        print(*[unmask(x) for x in path[:path_len]], file=out_file)

    def test_prime():
        nonlocal OPER_COUNTER
        OPER_COUNTER = 0
        n = secret_int(int(in_file.readline()))
        res = konstant.is_prime(n)
        #print(OPER_COUNTER)
        if OPER_COUNTER > 1000000:
            print(-1, file=out_file)
        else:
            print(unmask(res), file=out_file)

    subtask_num, test_count = map(int, in_file.readline().split())
    assert subtask_num in range(0, 5)
    for _ in range(test_count):
        KEY_A = secrets.randbits(32)
        if subtask_num == 0:
            test_ith_element()
        elif subtask_num == 1:
            test_sort()
        elif subtask_num == 2:
            test_connected_components()
        elif subtask_num == 3:
            test_graph_path()
        elif subtask_num == 4:
            test_prime()

if __name__ == "__main__":
    main()
