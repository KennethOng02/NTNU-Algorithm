#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
}

int lcs(const vector<int>& seq1, const vector<int>& seq2) {
  unordered_map<int, vector<int>> index_map;
  for(int i = seq1.size() - 1; i >= 0; i--)
    index_map[seq1[i]].push_back(i);

  vector<int> indices;
  for(int i = 0; i < seq2.size(); i++)
    indices.insert(indices.end(), index_map[seq2[i]].begin(), index_map[seq2[i]].end());

  // calculate LIS
  // O(nlogn)
  vector<int> lis;
  vector<int>::iterator it;
  for(int i = 0; i < indices.size(); i++) {
    it = lower_bound(lis.begin(), lis.end(), indices[i]); // O(logn)
    if(it == lis.end())
      lis.push_back(indices[i]);
    else
      *it = indices[i];
  }

  return lis.size();
}

int main() {
  fast_io();

  int airport_num_1, airport_num_2;
  cin >> airport_num_1 >> airport_num_2;

  vector<int> airport_1(airport_num_1);
  for(int &a : airport_1)
    cin >> a;

  vector<int> airport_2(airport_num_2);
  for(int &a : airport_2)
    cin >> a;

  cout << lcs(airport_1, airport_2) << '\n';

  return 0;
}