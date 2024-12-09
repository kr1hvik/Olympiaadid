#include <iostream>
#include <iomanip> // setprecision
#include <algorithm> // max
#include <cmath> // abs
using namespace std;

double solve(int m, int n, int x1, int y1, int x2, int y2) {
    if (x1 == x2) return max(m - x1, x1) * n;
    if (y1 == y2) return max(n - y1, y1) * m;
    return m * n - abs((x1 - x2) * (y1 - y2)) / 2.0;
}

int main () {
    int m, n, x1, y1, x2, y2;
    cin >> m >> n >> x1 >> y1 >> x2 >> y2;
    cout << setprecision(12) << solve(m, n, x1, y1, x2, y2) << endl;
}
