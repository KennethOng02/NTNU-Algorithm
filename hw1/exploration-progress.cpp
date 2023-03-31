#include <iostream>
using namespace std;

void fastIO() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
}

void print_arr(int *arr, int n) {
  for(int i = 0; i < n; i++)
    cout << arr[i] << ' ';
  cout << '\n';
}

int main() {
  fastIO();

  int region_num, day_num;
  cin >> region_num >> day_num;

  int *goal = new int [region_num];
  for(int i = 0; i < region_num; i++) {
    cin >> goal[i];
  }
  // print_arr(goal, region_num);

  // create the diff array
  int *diff = new int [region_num];
  diff[0] = goal[0];
  for(int i = 1; i < region_num; i++) {
    diff[i] = goal[i] -  goal[i - 1];
  }
  // print_arr(diff, region_num);

  int first, second, progress, sum;
  bool completed = false;
  for(int i = 0; i < day_num; i++) {
    cin >> first >> second >> progress; 

    // update the diff arr
    diff[first] -= progress;
    if(second < region_num - 1) {
      diff[second + 1] += progress;
    }

    // check if exploration completed
    sum = diff[0];
    for(int j = 1; sum <= 0 && j < region_num; j++) {
      if(sum > 0) 
        break;
      else {
        if(j == region_num - 1)
          completed = true;
      }
      sum += diff[j];
    }

    if (completed) {
      cout << i + 1 << '\n';
      return 0;
    }
  }
  cout << -1 << '\n';

  return 0;
}
