#include <iostream>
#include <vector>
#include <climits>
#include <string>
#include <queue>
using namespace std;

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
}

class Graph {
  int station_num, source, sink;
  vector<int> current;
  vector<int> required;
  vector<vector<int>> graph;
  vector<vector<int>> residual_graph;

  public:
    Graph(int station_num) {
      this->station_num = station_num;
      this->source = 0;
      this->sink = station_num + 1;
      get_input();
    }

    void get_input() {
      int num;
      for(int i = 0; i < station_num; ++i) {
        cin >> num;
        current.push_back(num);
      }

      for(int i = 0; i < station_num; ++i) {
        cin >> num;
        required.push_back(num);
      }

      graph.resize(station_num + 2, vector<int>(station_num + 2));
      residual_graph.resize(station_num + 2, vector<int>(station_num + 2));

      for(int i = 0; i < station_num; ++i) {
        graph[0][i + 1] = current[i];
      }

      for(int i = 0; i < station_num; ++i) {
        for(int j = 0; j < station_num; ++j) {
          cin >> num;
          graph[i + 1][j + 1] = num;
        }
        graph[i + 1][station_num + 1] = required[i];
      }

      station_num += 2;
    }

    void print_size() {
      for(auto i : graph) {
        for(auto j : i) {
          cout << j << ' ';
        }
        cout << endl;
      }
    }

    bool bfs(vector<vector<int>> adj, vector<int>& parent) {
      vector<bool> visited(station_num, false);

      queue<int> q;
      q.push(source);
      visited[source] = true;
      parent[source] = -1;

      while(!q.empty()) {
        int u = q.front(); 
        q.pop();

        for(int v = 0; v < station_num; v++) {
          if(visited[v] == false && adj[u][v] > 0) {
            if(v == sink) {
              parent[v] = u;
              return true;
            }
            q.push(v);
            parent[v] = u;
            visited[v] = true;
          }
        }
      }
      return false;
    }

    int ford_fulkerson() {
      int u, v;
      for(int i = 0; i < station_num; ++i) {
        for(int j = 0; j < station_num; ++j) {
          residual_graph[i][j] = graph[i][j];
        }
      }

      vector<int> parent(station_num, 0);

      int max_flow = 0;

      while(bfs(residual_graph, parent)) {
        int path_flow = INT_MAX;

        for(v = sink; v != source; v = parent[v]) {
          u = parent[v];
          path_flow = min(path_flow, residual_graph[u][v]);
        }

        for(v = sink; v != source; v = parent[v]) {
          u = parent[v];
          residual_graph[u][v] -= path_flow;
          residual_graph[v][u] += path_flow;
        }

        max_flow += path_flow;
      }
      int sum = 0;
      for(int i = 0; i < station_num - 2; ++i) {
        sum += required[i];
      }
      // cout << sum << endl;
      // cout << max_flow << endl;
      return sum - max_flow;
    }
};

int main() {
    fast_io();

    int station_num;
    cin >> station_num;

    Graph g(station_num);

    // g.print_size();

    cout << g.ford_fulkerson() << endl;
}
