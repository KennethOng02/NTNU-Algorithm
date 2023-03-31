#include <iostream>
using namespace std;

void fastIO() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
}

int find_pos(int *arr, int n, int idx) {
  int result = 0; 
  for (int i = 0; i < n; i++) { 
    if (arr[i] < arr[idx]) 
      result++; 

    if (arr[i] == arr[idx] && i < idx) 
      result++; 
  } 
  return result + 1;  
}

int main() {
  fastIO();

  int res_num, op_num;
  cin >> res_num >> op_num;

  int *arr = new int [res_num];
  for(int i = 0; i < res_num; i++) {
    cin >> arr[i];
  }
  int op, first, second, target, pos;
  for(int i = 0; i < op_num; i++) {
    cin >> op;
    if(op == 1) {
      cin >> first >> second;
      arr[first - 1] = second;
    }else {
      cin >> first;
      cout << find_pos(arr, res_num, first - 1);
    }
  }

  return 0;
}
