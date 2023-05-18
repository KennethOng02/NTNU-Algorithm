#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
}

void print_adj(vector<vector<int>> adj, int num) {
  for(vector<int> i : adj) {
    for(int x : i)
      cout << x << " ";
    cout << '\n';
  }
}

void dfs(int u, int v, const vector<vector<int>>& adj, vector<int>& pre, vector<int>& low, vector<pair<int, int>>& critical) {
  static int cnt = 0;
  pre[v] = low[v] = cnt++;
  for(int w : adj[v]) {
    if(pre[w] == -1) {
      dfs(v, w, adj, pre, low, critical);
      low[v] = min(low[v], low[w]);
      if(low[w] == pre[w]) {
        if(v <= w)
          critical.push_back(make_pair(v, w));
        else
          critical.push_back(make_pair(w, v));
      }
    }else if(w != u) {
      low[v] = min(low[v], pre[w]);
    }
  }
}

int main() {
  fast_io();

  int shop_num, road_num;
  cin >> shop_num >> road_num;
  
  vector<vector<int>> adj(shop_num);
  int first, second;
  for(int i = 0; i < road_num; ++i) {
    cin >> first >> second;
    adj[first].push_back(second); 
    adj[second].push_back(first); 
  }

  /* print_adj(adj, shop_num); */

  vector<int> pre(shop_num, -1);
  vector<int> low(shop_num, -1);
  vector<pair<int, int>> critical;

  for(int i = 0; i < shop_num; ++i) {
    if(pre[i] == -1)
      dfs(i, i, adj, pre, low, critical);
  }
  
  if(critical.empty())
    cout << "No Critical Road" << '\n';
  else {
    sort(critical.begin(), critical.end());
    for(pair<int, int> p : critical) {
      cout << p.first << ' ' << p.second << '\n';
    }
  }
}