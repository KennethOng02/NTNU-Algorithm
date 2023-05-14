#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
}

void print_2dvec(vector<vector<long>>& vec) {
  for(vector<long> row : vec) {
    for(long node : row) {
      cout << node << ' ';
    }
    cout << '\n';
  }
}

int main() {
  fast_io();
  int num;
  cin >> num;
  vector<long> bst(num);
  for(long &node : bst)
    cin >> node;
  sort(bst.begin(), bst.end());

  vector<vector<long>> dp(num, vector<long> (num, -1));

  for(int i = 0; i < num; i++)
    dp[i][i] = bst[i];

  for(int i = 0; i < num - 1; i++)
    dp[i][i + 1] = bst[i] + bst[i + 1];

  long max_path;
  for(int i = 2; i < num; i++) {
    for(int j = 0; j < num - i; j++) { // loop diagonalongy
      // cout << "row: " << j << ' ' << "col: " << i + j << '\n';
      for(int k = j + 1; k < i + j; k++) { // make each as root
        // cout << "root: " << k << '\n';
        max_path = bst[k] + max(dp[j][k - 1], dp[k + 1][i + j]);
        // cout << max_path << '\n';
        dp[j][i + j] = dp[j][i + j] < 0 || max_path < dp[j][i + j] ? max_path : dp[j][i + j];
      }
    }
  }
  print_2dvec(dp);
  cout << dp[0][num - 1];
}
