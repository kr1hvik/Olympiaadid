// O(n) with trie

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

const int maxs = 1e6 + 5;

int child [maxs][26]; // 0 = not present
int age [maxs];
int vc = 1;

void insert (int u, const string& s, int pos, int lab) {
  if (pos == (int) s.size()) {
    return;
  }

  if (child[u][s[pos] - 'a'] == 0 && lab == 0) {
    vc++;
    child[u][s[pos] - 'a'] = vc;
    
    age[child[u][s[pos] - 'a']] = lab;
    insert(child[u][s[pos] - 'a'], s, pos + 1, lab);
  } else if (age[child[u][s[pos] - 'a']] >= lab - 1) {
    age[child[u][s[pos] - 'a']] = lab;
    insert(child[u][s[pos] - 'a'], s, pos + 1, lab);
  }  
}

int depth [maxs];
int par [maxs];
char let [maxs];

void dfs (int u, int n, pair<int, int> &best) { 
  for (int i = 0; i < 26; i++) {
    if (child[u][i] == 0)
      continue;

    int v = child[u][i];
    if (age[v] != n - 1)
      continue;
    
    depth[v] = depth[u] + 1;
    par[v] = u;
    let[v] = 'a' + i;

    dfs(v, n, best);
  }

  if (depth[u] > best.first)
    best = make_pair(depth[u], u);
}

int main () {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int m, n;
  cin >> m >> n;

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
