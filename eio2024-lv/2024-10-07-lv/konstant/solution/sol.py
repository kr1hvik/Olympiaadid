from secret_int import secret_int

# 0 -> 0, 1 -> 0xffffffff
def bit_broadcast(x):
    return -x

def select(cond, t, f):
    return (cond & t) | (~cond & f)

def ith_element(A, i):
    res = secret_int(0)
    for j, x in enumerate(A):
        res |= (i == j) * x
    return res

def cmp_sort(A, i, j):
    a_lt_b = bit_broadcast(A[i] < A[j])
    min = select(a_lt_b, A[i], A[j])
    max = select(a_lt_b, A[j], A[i])
    A[i] = min
    A[j] = max

def sort_arr(A):
    n = len(A)
    p = 0
    while 1<<p < n:
        k = p
        while k >= 0:
            K = 1<<k
            for j in range(0 if k == p else K, n-K, 2*K):
                for i in range(min(K, n-j-K)):
                    if (i+j) >> (1+p) == (i+j+K) >> (1+p):
                        cmp_sort(A, i+j, i+j+K)
            k -= 1
        p += 1

def connected_components(A):
    n = len(A)
    components = list(range(n))
    component_count = n
    for i in range(n):
        for j in range(i+1, n):
            do_conn = A[i][j]
            component_count -= do_conn * (components[i] != components[j])
            # replace all instances of components[i] with components[j]
            from_ = components[i]
            delta = do_conn * (components[j] - components[i])
            for k in range(n):
                components[k] += (components[k] == from_) * delta

    return component_count

def graph_path(A, start, end):
    n = len(A)
    dist = [[0] * n for _ in range(n)]
    prev = [[0] * n for _ in range(n)]
    for i in range(n):
        for j in range(n):
            is_edge = bit_broadcast(A[i][j] != 0)
            dist[i][j] = select(is_edge, A[i][j], 0xffff_ffff)
            prev[i][j] = select(is_edge, i, 0)

    for i in range(n):
        dist[i][i] = 0
        prev[i][i] = i

    for k in range(n):
        for i in range(n):
            for j in range(n):
                cond = dist[i][j] > dist[i][k] + dist[k][j]
                cond &= dist[i][k] + dist[k][j] > dist[i][k] # check that addition doesn't overflow
                improve = bit_broadcast(cond)
                dist[i][j] = select(improve, dist[i][k] + dist[k][j], dist[i][j])
                prev[i][j] = select(improve, prev[k][j], prev[i][j])
    
    the_distance = 0
    for i in range(n):
        for j in range(n):
            the_distance |= ((i == start) & (j == end)) * dist[i][j]

    cur = end
    path = [cur]
    path_length = 1
    for k in range(1, n):
        path_member = 0
        for i in range(n):
            for j in range(n):
                correct = ((i == start) & (j == cur))
                path_member |= correct * prev[i][j]
        path.append(path_member)
        path_length += (cur != start)
        cur = path_member

    path.reverse()
    for i in range(n):
        correct = bit_broadcast(i >= path_length)
        for j in range(1, n):
            temp = path[j-1]
            path[j-1] = select(correct, path[j], path[j-1])
            path[j] = select(correct, temp, path[j])

    return (the_distance, path_length, path)

# c++ solution has more comments

def ctz(x):
    c = 32
    v = x & -x
    c -= (v != 0)
    c -= ((v & 0x0000ffff) != 0) << 4
    c -= ((v & 0x00ff00ff) != 0) << 3
    c -= ((v & 0x0f0f0f0f) != 0) << 2
    c -= ((v & 0x33333333) != 0) << 1
    c -= ((v & 0x55555555) != 0)
    return c

def modmul(a, b, mod):
    res = 0
    for _ in range(32):
        res += (b & 1) * (a - (res >= mod - a)*mod)
        b >>= 1
        a = a + a - (a > mod - a) * mod
    return res

def modpow(base, exp, mod):
    res = 1
    for _ in range(32):
        res = select(bit_broadcast(exp & 1), modmul(res, base, mod), res)
        exp >>= 1
        base = modmul(base, base, mod)
    return res

def miller_rabin_trial(n, s, a):
    d = (n - 1) >> s
    x = modpow(a, d, n)
    is_prime = 1
    for i in range(32):
        y = modmul(x, x, n)
        is_prime &= 1-((i < s) & (y == 1) & (x != 1) & (x != n-1))
        x = y
        is_prime &= 1-(((i + 1) == s) & (y != 1))
    return is_prime


def is_prime(n):
    s = ctz(n - 1)
    res = (n & 1)
    res &= miller_rabin_trial(n, s, 2)
    res &= (n <= 7) | miller_rabin_trial(n, s, 7)
    res &= (n <= 61) | miller_rabin_trial(n, s, 61)
    return res | (n == 2)
