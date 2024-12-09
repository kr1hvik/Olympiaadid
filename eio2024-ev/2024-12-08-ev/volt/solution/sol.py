def solve(m, n, x1, y1, x2, y2):
    if x1 == x2: return max(m - x1, x1) * n
    if y1 == y2: return max(n - y1, y1) * m
    return m * n - abs((x1 - x2) * (y1 - y2)) / 2.0

m, n, x1, y1, x2, y2 = (int(x) for x in input().split())
print(solve(m, n, x1, y1, x2, y2))
