// O(n log^2 n) with trie and small to large merging
// kinda silly but probably should pass

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

const int maxs = 1e6 + 5;

template<typename T>
T* merge (T* p, T* q) {
  if (p->size() < q->size())
    swap(p, q);

  for (auto x = q->begin(); x != q->end(); x++)
    p->insert(*x);

  return p;
}

int child [maxs][26]; // 0 = not present
set<int>* labels [maxs];
int vc = 1;

void insert (int u, const string& s, int pos, int lab) {
  if (pos == (int) s.size()) {
    labels[u]->insert(lab);
    return;
  }

  if (child[u][s[pos] - 'a'] == 0) {
    vc++;
    child[u][s[pos] - 'a'] = vc;
    labels[vc] = new set<int>();
  }

  insert(child[u][s[pos] - 'a'], s, pos + 1, lab);
}

int depth [maxs];
int par [maxs];
char let [maxs];

void dfs (int u, int n, pair<int, int> &best) { 
  for (int i = 0; i < 26; i++) {
    if (child[u][i] == 0)
      continue;

    int v = child[u][i];
    depth[v] = depth[u] + 1;
    par[v] = u;
    let[v] = 'a' + i;

    dfs(v, n, best);
    labels[u] = merge(labels[u], labels[v]);
  }

  if ((int) labels[u]->size() == n)
    if (depth[u] > best.first)
      best = make_pair(depth[u], u);
}

int main () {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int m, n;
  cin >> m >> n;

  labels[1] = new set<int>();
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      string s;
      cin >> s;
  
      insert(1, s, 0, i);
    }
  }

  auto best = make_pair(-1, -1);
  dfs(1, n, best);

  vector<char> path;
  for (int u = best.second; u != 1; u = par[u])
    path.push_back(let[u]);

  reverse(path.begin(), path.end());
  for (char c : path)
    cout << c;
  cout << '\n';
}
