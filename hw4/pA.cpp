#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <unordered_map>
using namespace std;

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
}

class Town {
  int town_num, road_num, stop_num;
  unordered_map<string, int> town_umap;
  vector<int> seq;
  int **graph;
  
  public:
    Town(int town_num, int road_num, int stop_num) {
      this->town_num = town_num;
      this->road_num = road_num;
      this->stop_num = stop_num;
      graph = new int*[town_num];
      for(int i = 0; i < town_num; ++i) {
        graph[i] = new int[town_num];
        for(int j = 0; j < town_num; ++j) {
          graph[i][j] = (i == j) ? 0 : INT_MAX;
        }
      }
      add_edge();
    }
      
    void add_edge() {
      string t1, t2;
      int weight, town_1, town_2;
      int cur_num = 0;
      for(int i = 0; i < road_num; ++i) {
        cin >> t1 >> t2 >> weight;
        if(town_umap.count(t1) == 0) town_umap.insert({t1, cur_num++});
        if(town_umap.count(t2) == 0) town_umap.insert({t2, cur_num++});
        town_1 = town_umap.at(t1);
        town_2 = town_umap.at(t2);
        if(weight < graph[town_1][town_2]) {
          graph[town_1][town_2] = graph[town_2][town_1] = weight;
        }
      }
      string town;
      for(int i = 0; i < stop_num; ++i) {
        cin >> town;
        seq.push_back(town_umap.at(town));
      }
    }

    void print_graph() {
      for(int i = 0; i < town_num; ++i) {
        for(int j = 0; j < town_num; ++j) {
          cout << graph[i][j] << ' ';
        }
        cout << endl;
      }
    }

    void floyd_warshall() {
      for(int k = 0; k < town_num; ++k) {
        for(int i = 0; i < town_num; ++i) {
          for(int j = 0; j < town_num; ++j) {
            if(graph[i][j] > graph[i][k] + graph[k][j] && (graph[i][k] + graph[k][j]) > 0) {
              graph[i][j] = graph[i][k] + graph[k][j];
            }
          }
        }
      }
    }

    int find_min_dist() {
      floyd_warshall();
      int total_dist = 0;
      int first, second;
      for(int i = 0; i < seq.size() - 1; ++i) {
        first = seq[i];
        second = seq[i + 1];
        total_dist += graph[first][second]; 
      }
      return total_dist;
    }
};

int main() {
  fast_io();

  int town_num, road_num, stop_num;
  cin >> town_num >> road_num >> stop_num;
  
  Town t(town_num, road_num, stop_num);

  cout << t.find_min_dist() << endl;
}
