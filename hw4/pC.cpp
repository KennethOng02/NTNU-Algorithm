#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <climits>
using namespace std;

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
}

void dijkstra(vector<vector<pair<int, int>>>& adj_list, int city_num, int source, int destination) {
  city_num = city_num * 2;
  vector<int> dist(city_num + 1, 0x3f3f3f3f);
  vector<int> total(city_num + 1, 0);
  vector<bool> visited(city_num + 1, false);

  dist[source] = 0;
  total[source] = 1;
  visited[0] = true;
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;
  Q.push({0, source});

  while(!Q.empty()) {
    int u = Q.top().second;
    Q.pop();

    if(!visited[u]) {
      visited[u] = true;

      for(auto &it : adj_list[u]) {
        int v = it.first;
        int weight = it.second;

        if(dist[u] + weight <= dist[v]) {
          dist[v] = dist[u] + weight;
          total[v] = total[u] + 1;
          Q.push({dist[v], v});
        }
      }
    }
  }

  cout << dist[city_num] << ' ' << total[destination] - 2 << endl;
}

int main() {
  fast_io();

  int city_num, flight_num, source, destination;

  cin >> city_num >> flight_num;

  source = 1;
  destination = city_num * 2;
  
  vector<vector<pair<int, int>>> adj_list(city_num * 2 + 1);

  int city_1, city_2, cost;
  for(int i = 0; i < flight_num; ++i) {
    cin >> city_1 >> city_2 >> cost;

    adj_list[city_1].push_back({city_2, cost});
    adj_list[city_2].push_back({city_1, cost});

    adj_list[city_1 + city_num].push_back({city_2 + city_num, cost});
    adj_list[city_2 + city_num].push_back({city_1 + city_num, cost});

    adj_list[city_1].push_back({city_2 + city_num, 0});
    adj_list[city_2].push_back({city_1 + city_num, 0});
  }

  dijkstra(adj_list, city_num, source, destination);
}
