import konstant
from secret_int import secret_int

def test_ith_element():
    _n, i = map(int, input().split())
    i = secret_int(i)
    a = [secret_int(int(x)) for x in input().split()]
    res = konstant.ith_element(a, i)
    print(res.DEBUG_value)

def test_sort():
    _n = input()
    a = [secret_int(int(x)) for x in input().split()]
    konstant.sort_arr(a)
    print(*[x.DEBUG_value for x in a])

def test_connected_components():
    n = int(input())
    A = []
    for _ in range(n):
        A.append([secret_int(int(x)) for x in input().split()])
    res = konstant.connected_components(A)
    print(res.DEBUG_value)

def test_graph_path():
    n, start, end = map(int, input().split())
    start, end = map(secret_int, [start, end])
    A = []
    for _ in range(n):
        A.append([secret_int(int(x)) for x in input().split()])
    res = konstant.graph_path(A, start, end)
    (distance, path_len, path) = res
    print(distance.DEBUG_value)
    path_len = path_len.DEBUG_value
    assert path_len <= len(path)
    print(path_len)
    print(*[x.DEBUG_value for x in path[:path_len]])

def test_prime():
    n = secret_int(int(input()))
    res = konstant.is_prime(n)
    print(res.DEBUG_value)

subtask_num, test_count = map(int, input().split())
assert subtask_num in range(0, 5)
for _ in range(test_count):
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
