#include <iostream>
#include <bitset>
#include <queue>
#include <vector>
#include <fstream>
const int MAX_E = 1005;
const int MAX_V = 1005;
const int MOD = 1e9 + 7;

using namespace std;

bool operator< (bitset<MAX_E> p, bitset<MAX_E> q) {
  for (int i = MAX_E - 1; i >= 0; i--) {
    if (p[i] != q[i]) {
      return !p[i];
    }
  }

  return false;
}

bool operator> (bitset<MAX_E> p, bitset<MAX_E> q) {
  for (int i = MAX_E - 1; i >= 0; i--) {
    if (p[i] != q[i]) {
      return p[i];
    }
  }

  return false;
}

struct bitcmp {
  bool operator() (pair<bitset<MAX_E>, int> p, pair<bitset<MAX_E>, int> q) {
    if (p.first == q.first) {
      return p.second < q.second;
    } else {
      return p.first > q.first;
    }
  }
};

struct Edge {
  int other_vertex, logweight;

  Edge () {
  }

  Edge (int _other_vertex, int _logweight) {
    other_vertex = _other_vertex;
    logweight = _logweight;
  }
};

class Graph {
  int vertexc;
  vector<vector<Edge> > adjacency;

public:
  Graph (int _vertexc) {
    vertexc = _vertexc;
    adjacency = vector<vector<Edge> > (vertexc + 5, vector<Edge> (0));
  }

  void add_edge (int u, int v, int logweight) {
    adjacency[u].push_back(Edge(v, logweight));
    adjacency[v].push_back(Edge(u, logweight));
  }
  
  int query (int p, int q) {
    vector<bitset<MAX_E> > dist (vertexc + 5, (bitset<MAX_E> (0)).flip());
    dist[p] = bitset<MAX_E> (0);    
 
    priority_queue<pair<bitset<MAX_E>, int>,
                   vector<pair<bitset<MAX_E>, int> >,
                   bitcmp > que;
    que.push(make_pair(dist[p], p));

    while (!que.empty()) {
      pair<bitset<MAX_E>, int> qtop = que.top();
      que.pop();

      bitset<MAX_E> qdist = qtop.first;
      int qvertex = qtop.second;

      if (qdist == dist[qvertex]) {
        for (Edge e : adjacency[qvertex]) {
          bitset<MAX_E> nxtdist = bitset<MAX_E> (0);
          nxtdist[e.logweight] = 1;
          nxtdist |= qdist;

          if (nxtdist < dist[e.other_vertex]) {
            dist[e.other_vertex] = nxtdist;
            que.push(make_pair(nxtdist, e.other_vertex));
          }
        }
      }
    }

    bitset<MAX_E> ans = dist[q];
    
    int int_ans = 0, cur_power = 1;
    for (int i = 0; i < MAX_E; i++) {
      if (ans[i]) {
        int_ans += cur_power;
        int_ans %= MOD;
      }

      cur_power += cur_power;
      cur_power %= MOD;
    }

    return int_ans;
  }
};

int main () {
  int vertexc, edgec, queryc;
  ifstream fin("rallisis.txt");
  ofstream fout("rallival.txt");
  
  fin >> vertexc >> edgec >> queryc;

  Graph world (vertexc);
  for (int i = 1; i <= edgec; i++) {
    int u, v;
    fin >> u >> v;

    world.add_edge(u, v, i);
  }

  for (int i = 1; i <= queryc; i++) {
    int p, q;
    fin >> p >> q;

    fout << world.query(p, q) << '\n';
  }
}
