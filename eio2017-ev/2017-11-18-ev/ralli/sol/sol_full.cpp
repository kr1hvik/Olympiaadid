/* Idee: Tähvend Uustalu
 * Tekst: Taavet Kalda, Tähvend Uustalu
 *
 * Lahendus:
 * Sisuliselt küsitakse meilt lühimaid teid graafis, kus
 * k-nda serva kaal on 2^k. Vaatleme k-ndat serva. Kui
 * selle serva ühest otspunktist on võimalik jõuda teise,
 * kasutades vaid servi, mille indeksid on väiksemad kui k,
 * siis pole k-ndat serva üldse vaja, sest odavam on kasutada
 * servi, mille indeksid on väiksemad kui k. Tähendab, kõik
 * lühimad teed asuvad graafi minimaalsel toesepuul. Puude peal
 * on lühimate teede leidmine aga oluliselt lihtsam ning päringutele
 * on võimalik vastata O(log V) ajas.
 *
 * Minimaalse toesepuu leidmiseks kasutame Kruskali algoritmi.
 * Hakkame puusse servi lisama, kergeimast alates. Kui lisatava serva otspunktid
 * asuvad juba graafi ühes ja samas sidususkomponendis, siis jätame
 * serva lisamata. Samas sidususkomponendis olemiseks kasutame
 * union-find andmestruktuuri. Selle sammu keerukus on kokku O(E log V).
 *
 * Kuidas leida lühimaid teid puus? Selleks kasutame nn. kahendtõstuki
 * meetodit. Juurestame esiteks puu. Jätame iga tipu kohta meelde tema
 * esimese, teise, neljanda, kaheksanda jne eellase. Samuti jätame iga
 * tipu kohta meelde teepikkuse tema esimesse, teisse, neljandasse,
 * kaheksandasse jne eellasesse. Seda saab kiiresti teha, sest iga
 * tipu 2k-s eellane on tema k-nda eellase k-s eellane. Lõpuks jätame
 * meelde, mitmendal tasandil iga tipp puus asub, s.o. mitu serva
 * jääb antud tipu ja juure vahele. Selle sammu keerukus on O(V log V),
 * sest iga tipu kohta on vaja jätta meelde O(log V) eellast.
 * 
 * Kui see kõik on tehtud, saame hakata päringutele vastama. Kui meilt
 * küsitakse teepikkust p ja q vahel, siis viime esiteks tipud p ja q
 * samale tasandile. Kasutades varem arvutatud eellasi, võime seda teha
 * vaid log(V) hüppega. Edasi tarvitame kahendotsingut, et leida p ja q
 * madalaim ühine eellane, ning sealt saame kiiresti arvutada otsitava
 * teepikkuse.
 */

#include <iostream>
#include <vector>
#include <assert.h>
#include <fstream>

using namespace std;

const int MOD = 1e9 + 7;
const int MAX_LG = 22;

struct Modint {
  int value;

  Modint () {
    value = 0;
  }

  Modint (int _value) {
    value = _value % MOD;
  }
};

Modint operator+ (Modint p, Modint q) {
  return Modint(p.value + q.value);
}

class DSU {
  /* Union-find andmestruktuur. Võimaldab kontrollida, kas kaks
   * tippu asuvad graafi ühes ja samas sidususkomponendis.
   * Samuti võimaldab serva lisamist kahe tipu vahele.
   * Käesolevas implementatsioonis on päringu keerukus O(log V) */
   
  vector<int> root;
  int vertexc;
  
public:
  DSU (int _vertexc) {
    vertexc = _vertexc;

    root = vector<int> (vertexc + 5, 0);
    for (int i = 0; i <= vertexc; i++) {
      root[i] = i;
    }
  }

  int find (int vertex) {
    if (root[vertex] == vertex) {
      return root[vertex];
    } else {
      root[vertex] = find(root[vertex]);
      return root[vertex];
    }
  }

  void merge (int u, int v) {
    u = find(u);
    v = find(v);

    root[u] = v;
  }
};

struct Edge {
  int other_vertex;
  Modint weight;

  Edge () {
  }

  Edge (int _other_vertex, Modint _weight) {
    other_vertex = _other_vertex;
    weight = _weight;
  }
};

class Tree {
  int vertexc;
  vector<int> level;
  vector<vector<int> > par;
  vector<vector<Modint> > parcost;
  vector<vector<Edge> > adjacency;

public:
  Tree (int _vertexc) {
    vertexc = _vertexc;
    
    level = vector<int> (vertexc + 5, 0);
    par = vector<vector<int> > (vertexc + 5);
    parcost = vector<vector<Modint> > (vertexc + 5);
    adjacency = vector<vector<Edge> > (vertexc + 5, vector<Edge> (0));
  }

  void add_edge (int u, int v, Modint weight) {
    adjacency[u].push_back(Edge(v, weight));
    adjacency[v].push_back(Edge(u, weight));
  }

  void build () {
    vector<int> visited (vertexc + 5, 0);
    vector<pair<int, Edge> > que;
    que.push_back(make_pair(1, Edge(1, Modint(0))));
    visited[1] = 1;
    for (int i = 0; i < (int) que.size(); i++) {
      int vertex = que[i].first;
      int parent = que[i].second.other_vertex;
      Modint par_w = que[i].second.weight;

      level[vertex] = level[parent] + 1;

      par[vertex] = vector<int> (MAX_LG);
      par[vertex][0] = parent;
      for (int i = 1; i < MAX_LG; i++) {
        par[vertex][i] = par[par[vertex][i - 1]][i - 1];
      }

      parcost[vertex] = vector<Modint> (MAX_LG);
      parcost[vertex][0] = par_w;
      for (int i = 1; i < MAX_LG; i++) {
        parcost[vertex][i] = parcost[vertex][i - 1] +
          parcost[par[vertex][i - 1]][i - 1];
      }

      for (Edge e : adjacency[vertex]) {
        if (!visited[e.other_vertex]) {
          visited[e.other_vertex] = 1;
          que.push_back(make_pair(e.other_vertex, Edge(vertex, e.weight)));
        }
      }
    }
  }

  Modint query (int p, int q) {
    if (level[p] < level[q]) {
      swap(p, q);
    }

    Modint ans (0);
    /* Viime p ja q samale tasandile */
    int difference = level[p] - level[q];
    for (int i = 0; i < MAX_LG; i++) {
      if (difference & 1 << i) {
        ans = ans + parcost[p][i];
        p = par[p][i];
      }
    }

    if (p == q) {
      return ans;
    }

    /* Kahendotsing (sisuliselt) */
    for (int i = MAX_LG - 1; i >= 0; i--) {
      if (par[p][i] != par[q][i]) {
        ans = ans + parcost[p][i];
        ans = ans + parcost[q][i];

        p = par[p][i];
        q = par[q][i];
      }
    }

    ans = ans + parcost[p][0];
    ans = ans + parcost[q][0];

    return ans;
  }
};


int main () {
  int vertexc, edgec, queryc;
  ifstream fin("rallisis.txt");
  ofstream fout("rallival.txt");
  
  fin >> vertexc >> edgec >> queryc;

  Tree MST (vertexc);
  DSU connected (vertexc);

  Modint edge_weight (1);
  for (int i = 1; i <= edgec; i++) {
    edge_weight = edge_weight + edge_weight;

    int u, v;
    fin >> u >> v;

    /* Kruskali algoritm */
    if (connected.find(u) != connected.find(v)) {
      connected.merge(u, v);
      MST.add_edge(u, v, edge_weight);
    }
  }

  MST.build();

  for (int i = 1; i <= queryc; i++) {
    int p, q;
    fin >> p >> q;

    fout << MST.query(p, q).value << '\n';
  }
}
