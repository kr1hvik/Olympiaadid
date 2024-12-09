// esimene argument:
// 0 -> ei shuffle
// 1 -> shuffle
// teine argument 0 või 1 või 2
// kolmas argument
// 0 -> ara muuda
// 1 -> voimatu keskel (voib-olla)
// 2 -> voimatu alguses
// 3 -> voimatu lopus
// neljas argument: n
// viies argument: max suurus
// kuues argument: seeme
// seitsmes argument: ...

#include <bits/stdc++.h>
using namespace std;

mt19937 rng;

int rand(int a, int b) {
    return a + rng() % (b-a+1);
}

int main(int argc, char* argv[]) {
    int shuf = atoi(argv[1]);
    int tp1 = atoi(argv[2]);
    int tp2 = atoi(argv[3]);
    int n = atoi(argv[4]);
    int mx = atoi(argv[5]);
    int seed = atoi(argv[6]);
    int mitu = atoi(argv[7]);
    rng.seed(seed);

    vector<int> p(n,-1), m(n,-1);
    if (tp1 == 0) {
        p[0] = rand(5,20), m[0] = rand(5,20);
        for (int i = 1; i < n; ++i) {
            int suurenda = 1;
            if (rand(1,mitu)==mitu) {
                suurenda = rand(1, min((mx-10)/max(p[i-1],m[i-1]), 8));
            }
            p[i] = p[i-1]*suurenda;
            m[i] = m[i-1]*suurenda;
        }
    }
    else if (tp1 == 1) {
        vector<int> perm(n-1);
        iota(perm.begin(), perm.end(), 1);
        shuffle(perm.begin(), perm.end(), rng);
        p[0] = rand(5,8), m[0] = rand(5,8);
        vector<bool> inc(n,0);
        int s = min((mx-2)/max(p[0], m[0]),n-1);
        s = min(s, mitu);
        for (int i = 1; i < s; ++i) {
            inc[perm[i]] = 1;
        }
        int cur = 1;
        for (int i = 1; i < n; ++i) {
            if (inc[i]) ++cur;
            p[i] = p[0]*cur;
            m[i] = m[0]*cur;
        }
    }
    else if (tp1 == 2) {
        int cur1 = 1, cur2 = 1;
        for (int i = 0; i < n; ++i) {
            if (rand(1,mitu)==mitu && cur1 < mx) ++cur1;
            if (rand(1,mitu)==mitu && cur2 < mx) ++cur2;
            p[i] = cur1;
            m[i] = cur2;
        }
    }

    if (tp2==1) {
        for (int i = 1; i < n; ++i) {
            if (p[i] > p[i-1] && rand(0,1)==1) {
                if (rand(0,1)==0) p[i] = p[i-1];
                else m[i] = m[i-1];
                break;
            }
        }
    }
    else if (tp2==2) {
        do {
            p[0] = rand(1,4), m[0] = rand(1,4);
        } while (p[0] * m[0] == p[1] * m[1] || p[0] * m[1] == p[1] * m[0]);
    }
    else if (tp2==3) {
        do {
            p[n-1] = rand(p[n-2], mx), m[n-1] = rand(m[n-2],mx);
        } while (p[n-1] * m[n-1] == p[n-2] * m[n-2] || p[n-1] * m[n-2] == p[n-2] * m[n-1]);
    }

    if (shuf) {
        shuffle(p.begin(), p.end(), rng);
        shuffle(m.begin(), m.end(), rng);
    }

    cout << n << '\n';

    for (int i = 0; i < n; ++i) {
        cout << p[i] << " \n"[i==n-1];
    }

    for (int i = 0; i < n; ++i) {
        cout << m[i] << " \n"[i==n-1];
    }

    return 0;
}
