#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Graph {
  int vertex, edge;
  vector<pair<int, pair<int, int>>> edges;
  
  Graph(int vertex, int edge) {
    this->vertex = vertex;
    this->edge = edge;
  }
  
  void add_edge(int v1, int v2, int weight) {
    edges.push_back({weight, {v1, v2}});
  }
  
  void print_edges() {
    for(int i = 0; i < edge; ++i)
      cout << edges[i].second.first << ' ' << edges[i].second.second << ' ' << edges[i].first << '\n';
  }
  
  int find_max_st_bottleneck();
  int kruskal_mst(int bottleneck);
};

struct DisjointSets {
  int *parent, *rnk;
  int n;
  
  DisjointSets(int n) {
    this->n = n;
    parent = new int[n + 1];
    rnk = new int[n + 1];
    
    for(int i = 0; i <= n; i++) {
      rnk[i] = 0;
      parent[i] = i;
    }
  }
  
  int find(int u) {
    if(u != parent[u])
      parent[u] = find(parent[u]);
    return parent[u];
  }

  void merge(int x, int y) {
    x = find(x), y = find(y);

    if(rnk[x] > rnk[y])
      parent[y] = x;
    else
      parent[x] = y;

    if(rnk[x] == rnk[y])
      rnk[y]++;
  }
};

int Graph::find_max_st_bottleneck() {
  sort(edges.begin(), edges.end(), greater<>());
  
  DisjointSets ds(vertex);
  
  vector<pair<int, pair<int, int>>> mst;
  
  vector<pair<int, pair<int, int>>>::iterator it;
  for(it = edges.begin(); it != edges.end(); it++) {
    int u = it->second.first;
    int v = it->second.second;
    
    int set_u = ds.find(u);
    int set_v = ds.find(v);
    
    if (set_u != set_v) {
      mst.push_back({it->first, {u, v}});
      ds.merge(set_u, set_v);
    }
  }
  /* for(it = mst.begin(); it != mst.end(); it++) { */
  /*   cout << it->second.first << ' ' << it->second.second << ' ' << it->first << '\n'; */
  /* } */
  return mst.back().first;
}

int Graph::kruskal_mst(int bottleneck) {
  int mst_weight = 0;    
  
  sort(edges.begin(), edges.end());

  DisjointSets ds(vertex);
  
  vector<pair<int, pair<int, int>>>::iterator it;
  for(it = edges.begin(); it != edges.end(); it++) {
    if(it->first < bottleneck) {
      continue;
    }

    int u = it->second.first;
    int v = it->second.second;
    
    int set_u = ds.find(u);
    int set_v = ds.find(v);
    
    if(set_u != set_v) {
      /* cout << u << " - " << v << " : " << it->first << endl; */
      mst_weight += it->first;
      ds.merge(set_u, set_v);
    }
  }
  return mst_weight;
}

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
}

int main() {
  fast_io();

  int city_num, cable_num;
  cin >> city_num >> cable_num;

  Graph g(city_num, cable_num);

  int v1, v2, weight;
  for(int i = 0; i < cable_num; i++) {
    cin >> v1 >> v2 >> weight;
    g.add_edge(v1, v2, weight);
  }

  int bottleneck = g.find_max_st_bottleneck();
  cout << g.kruskal_mst(bottleneck) << '\n';

  return 0;
}