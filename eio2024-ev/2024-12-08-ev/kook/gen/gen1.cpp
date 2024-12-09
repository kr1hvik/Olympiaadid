// generaator juhuks n = 2
// esimene argument:
// 0 -> voimatu
// 1 -> p1 * m1 == p2 * m2
// 2 -> p1 * m2 == p2 * m1
// 3 -> p1 == p2 ja m1 == m2 
// teine argument: seeme

#include <bits/stdc++.h>
using namespace std;

mt19937 rng;

int rand(int a, int b) {
    return a + rng() % (b-a+1);
}

int main(int argc, char* argv[]) {
    int tp = atoi(argv[1]);
    int seed = atoi(argv[2]);
    rng.seed(seed);

    int p1 = -1, p2 = -1, m1 = -1, m2 = -1;
    if (tp==0) {
        do {
             p1 = rand(1, 1e3);
             p2 = rand(1, 1e3);
             m1 = rand(1, 1e3);
             m2 = rand(1, 1e3);
         } while (p1 * m1 == p2 * m2 || p1 * m2 == p2 * m1);
    }
    else if (tp==1) {
        int a = rand(1,100);
        int b = rand(1,100);
        int k1 = rand(1,10);
        int k2 = rand(1,10);
        p1 = a*k1;
        m1 = b*k2;
        p2 = a*k2;
        m2 = b*k1;
    }
    else if (tp==2) {
        int a = rand(1,100);
        int b = rand(1,100);
        int k1 = rand(1,10);
        int k2 = rand(1,10);
        p1 = a*k1;
        m1 = b*k1;
        p2 = a*k2;
        m2 = b*k2;
    }
    else {
        int p = rand(1,1000), m = rand(1,1000);
        p1 = p;
        p2 = p;
        m1 = m;
        m2 = m;
    }
    cout << "2\n";
    cout << p1 << ' ' << p2 << '\n';
    cout << m1 << ' ' << m2 << '\n';
    
    return 0;
}