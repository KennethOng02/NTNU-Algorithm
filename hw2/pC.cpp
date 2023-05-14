#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
}

void print_pair(const vector<pair<int, int>> pairvec) {
  cout << "---\n";
  for(const pair<int, int>& p : pairvec)
    cout << '(' << p.first << ',' << p.second << ')' << '\n';
  cout << "---" << '\n';
}

int main() {
  fast_io();

  int num_1, num_2;
  cin >> num_1 >> num_2;

  int flight_num;
  cin >> flight_num;

  vector<pair<int, int>> available_flight(flight_num);
  for(pair<int, int>& flight : available_flight)
    cin >> flight.first >> flight.second;

  sort(available_flight.begin(), available_flight.end(), 
    [](pair<int, int> f1, pair<int, int> f2){ 
      if(f1.first == f2.first)
        return f1.second > f2.second;
      else
        return f1.first < f2.first;
    }
  );

  // print_pair(available_flight);

  vector<int> dp;
  vector<int>::iterator it;
  for(int i = 0; i < flight_num; i++) {
    it = lower_bound(dp.begin(), dp.end(), available_flight[i].second);
    if(it == dp.end())
      dp.push_back(available_flight[i].second);
    else
      *it = available_flight[i].second;
  }

  cout << dp.size() << '\n';

  return 0;
}