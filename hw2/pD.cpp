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

  int num, total_length;
  cin >> num >> total_length;

  vector<pair<int, int>> audio_segments(num);
  for(pair<int, int>& segment : audio_segments)
    cin >> segment.first >> segment.second;

  // remove useless segment
  audio_segments.erase(remove_if(audio_segments.begin(), audio_segments.end(), [&](const pair<int, int>& i) {
    return i.first == i.second;
  }), audio_segments.end());

  // new segment number
  num = audio_segments.size();

  if(num == 0) {
    cout << "0 " << total_length << '\n';
    return 0;
  }

  // sort the segment
  sort(audio_segments.begin(), audio_segments.end(), 
    [](pair<int, int> f1, pair<int, int> f2){ 
      if(f1.first == f2.first)
        return f1.second > f2.second;
      else
        return f1.first < f2.first;
    }
  );

  // print_pair(audio_segments);

  vector<pair<int, int>> selected{audio_segments[0]};
  int distance = 0;
  int idx = 0;
  for(int i = 1; i < num; i++) {
    if(audio_segments[i].first > selected.back().second) {
      if(distance != 0)
        selected.push_back(audio_segments[idx]);
      if(audio_segments[i].first > selected.back().second)
        selected.push_back(audio_segments[i]);
      distance = 0;
      idx = 0;
    }
    if(audio_segments[i].first <= selected.back().second && audio_segments[i].second - selected.back().second > distance) {
      distance = audio_segments[i].second - selected.back().second;
      idx = i;
    }
  }
  if(idx != 0)
    selected.push_back(audio_segments[idx]);

  // print_pair(selected);

  // count the silence
  int s = selected.size();
  int silence = audio_segments[0].first;
  for(int i = 1; i < s; i++)
    if(selected[i].first > selected[i - 1].second)
      silence += selected[i].first - selected[i - 1].second;
  silence += total_length - selected.back().second;

  cout << s << ' ' << silence << '\n';

  return 0;
}
