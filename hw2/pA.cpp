#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#define ll long long
const ll MOD = pow(10, 9) + 7;

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
}

ll count_ways(int n) {
    vector<ll> dp(n + 1, 0);
    dp[0] = 1;
    for(ll j = 0; j < log2(n) + 1; j++) {
      int coin = pow(2, j);
      for(ll i = coin; i < n + 1; i++) {
        dp[i] += dp[i - coin];
        dp[i] = dp[i] % MOD;
      }
    }
    return dp[n];
}

int main() {
  fast_io();
  int num;
  cin >> num;
  cout << count_ways(num);
}
