#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
}

int lcs(vector<int>& seq1, vector<int>& seq2) {
  vector<vector<int>> index_map(1000001);
  for(int i = seq1.size() - 1; i >= 0; i--) {
    index_map[seq1[i]].push_back(i);
  }

  vector<int> indices;
  indices.reserve(seq2.size() * seq1.size() / index_map.size());

  for(int i = 0; i < seq2.size(); i++) {
    const vector<int>& indices_for_element = index_map[seq2[i]];
    indices.insert(indices.end(), indices_for_element.begin(), indices_for_element.end());
  }

  // calculate LIS
  // O(nlogn)
  vector<int> lis;
  lis.reserve(indices.size());
  for(int i = 0; i < indices.size(); i++) {
    int curr = indices[i];
    auto it = lower_bound(lis.begin(), lis.end(), curr);
    if(it == lis.end()) {
      lis.push_back(curr);
    }else {
      *it = curr;
    }
  }

  return lis.size();
}

int main() {
  fast_io();

  int airport_num_1, airport_num_2;
  cin >> airport_num_1 >> airport_num_2;

  vector<int> airport_1(airport_num_1);
  for(int i = 0; i < airport_num_1; ++i) {
    cin >> airport_1[i];
  }

  vector<int> airport_2(airport_num_2);
  for(int i = 0; i < airport_num_2; ++i) {
    cin >> airport_2[i];
  }

  cout << lcs(airport_1, airport_2) << '\n';

  return 0;
}
