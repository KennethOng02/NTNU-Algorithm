#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
using namespace std;

void fast_io() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
}

class Graph {
  int hotel_num, edge_num, start, end;
  vector<vector<pair<int, double>>> graph;

  public:
    Graph(int hotel_num, int edge_num) {
      this->hotel_num = hotel_num;
      this->edge_num = edge_num;
      for(int i = 0; i < hotel_num; ++i) {
        graph.push_back(vector<pair<int, double>>());
      }
      add_edge();
    }

    void add_edge() {
      int hotel_1, hotel_2;
      double success_prob;
      for(int i = 0; i < edge_num; ++i) {
        cin >> hotel_1 >> hotel_2 >> success_prob;
        graph[hotel_1].push_back({hotel_2, success_prob});
        graph[hotel_2].push_back({hotel_1, success_prob});
      }
      cin >> start >> end;
    }

    double max_success_prob() {
      vector<double> distance(hotel_num, 0.0);
      distance[start] = 1.0;
      priority_queue<pair<int, double>> q;
      q.push({start, 1.0});
      int node, next;
      double prob, next_prob, new_prob;

      while(!q.empty()) {
        node = q.top().first;
        prob = q.top().second;
        q.pop();

        if(prob < distance[node]) continue;

        for(const auto& neighbour : graph[node]) {
          next = neighbour.first;
          next_prob = neighbour.second;
          new_prob = distance[node] * next_prob;

          if(new_prob > distance[next]) {
            distance[next] = new_prob;
            q.push({next, new_prob});
          }
        }
      }
      return distance[end];
    }
};

int main() {
    fast_io();

    int hotel_num, edge_num;
    cin >> hotel_num >> edge_num;

    Graph g(hotel_num, edge_num);

    cout << fixed << setprecision(3) << g.max_success_prob() << endl;
}
