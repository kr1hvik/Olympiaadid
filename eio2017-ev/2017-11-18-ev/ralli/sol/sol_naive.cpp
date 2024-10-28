#include <iostream>
#include <fstream>
typedef long long llong;

using namespace std;

const int MOD = 1e9 + 7;
const int MAX_VERTEX = 55;
const llong INF = 1LL << 60;

llong dist [MAX_VERTEX][MAX_VERTEX];

int main () {
  for (int i = 0; i < MAX_VERTEX; i++) {
    for (int j = 0; j < MAX_VERTEX; j++) {
      if (i == j) {
        dist[i][j] = 0;
      } else {
        dist[i][j] = INF;
      }
    }
  }
  
  int vertexc, edgec, queryc;
  ifstream fin("rallisis.txt");
  ofstream fout("rallival.txt");
  fin >> vertexc >> edgec >> queryc;

  for (int i = 1; i <= edgec; i++) {
    int u, v;
    fin >> u >> v;

    dist[u][v] = min(dist[u][v], 1LL << i);
    dist[v][u] = min(dist[u][v], 1LL << i);
  }

  for (int k = 1; k <= vertexc; k++) {
    for (int i = 1; i <= vertexc; i++) {
      for (int j = 1; j <= vertexc; j++) {
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
      }
    }
  }
  
  for (int i = 0; i < queryc; i++) {
    int p, q;
    fin >> p >> q;

    fout << dist[p][q] % MOD << endl;
  }
}
