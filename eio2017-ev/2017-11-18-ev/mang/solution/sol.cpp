//Autor: Oliver-Matis Lill
//Idee: Lihtne BFS
#include<fstream>
#include<deque>
#include<vector>
using namespace std;

int main() {
    ifstream in("mangsis.txt");
    ofstream out("mangval.txt");

    int n;
    in >> n;

    vector<int> a(n);
    for(int i=0;i<n;i++) {
        in >> a[i];
    }

    vector<bool> explr(n, false);
    explr[0] = true;
    deque<int> front(1, 0);

    while(front.size() > 0) {
        int pos = front.front();
        front.pop_front();

        if(a[pos] == 0) {
            for(int d=1;d<=6;d++) {
                int next = (pos + d) % n;
                if(!explr[next]) {
                    explr[next] = true;
                    front.push_back(next);
                }
            }
        }
        else {
            int next = (pos + a[pos] + n) % n;
            if(!explr[next]) {
                explr[next] = true;
                front.push_back(next);
            }
        }
    }
    for(int i=0;i<n;i++) {
        out << explr[i] << " \n"[i == n-1];
    }

    return 0;
}
