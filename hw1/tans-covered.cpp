#include <iostream>
#include <vector>
using namespace std;

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
}
void print_board(vector<vector<int>>& board, int bsize) {
  for(int i = 0; i < bsize; i++) {
    for(int j = 0; j < bsize; j++)
      cout << board[j][i] << ' ';
    cout << '\n';
  }
}
void fill(vector<vector<int>>& board, int& counter, int x1, int y1, int x2, int y2, int x3, int y3) {
  board[x1][y1] = board[x2][y2] = board[x3][y3] = ++counter; 
}
void solve(vector<vector<int>>& board, int n, int& counter, int row, int col) {
  if(n == 2) { // stopping condition
    ++counter;
    for(int i = 0; i < n; i++) // fill the remaining white floor
      for(int j = 0; j < n; j++)
        if(board[row + i][col + j] == -1)
          board[row + i][col + j] = counter;
    return;
  }

  int bnum = 0; // number of black tile in this scope
  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)
      if(board[row + i][col + j] != -1) // non white
        bnum++;

  if(bnum == 1) {
    // locate the black tile
    int r, c;
    for(int i = 0; i < n; i++)
      for(int j = 0; j < n; j++)
        if(board[row + i][col + j] != -1) { // non white
          r = i;
          c = j;
        }
    if(r < n / 2 && c < n / 2) // first quad
      fill(board, counter, 
           row + n / 2 - 1, col + n / 2,
           row + n / 2, col + n / 2 - 1,
           row + n / 2, col + n / 2);
    else if(r < n / 2 && c >= n / 2) // second quad
      fill(board, counter, 
           row + n / 2 - 1, col + n / 2 - 1,
           row + n / 2, col + n / 2 - 1,
           row + n / 2, col + n / 2);
    else if(r >= n / 2 && c < n / 2) // third quad
      fill(board, counter, 
           row + n / 2 - 1, col + n / 2 - 1,
           row + n / 2 - 1, col + n / 2,
           row + n / 2, col + n / 2);
    else
      fill(board, counter, 
           row + n / 2 - 1, col + n / 2 - 1,
           row + n / 2 - 1, col + n / 2,
           row + n / 2, col + n / 2 - 1);
  }

  // divide and conquer
  solve(board, n / 2, counter, row, col);                 // first quad
  solve(board, n / 2, counter, row, col + n / 2);         // second quad
  solve(board, n / 2, counter, row + n / 2, col);         // third quad
  solve(board, n / 2, counter, row + n / 2, col + n / 2); // fourth quad
}
int main() {
  fast_io();

  int black_num, bsize;
  cin >> black_num >> bsize;

  vector<vector<int>> board(bsize, vector<int> (bsize));
  for(int i = 0; i < bsize; i++)
    for(int j = 0; j < bsize; j++)
      board[i][j] = -1;

  int bx, by;
  for(int i = 0; i < black_num; i++) {
    cin >> bx >> by;
    board[bx][by] = 0;
  }

  int counter = 0;

  solve(board, board.size(), counter, 0, 0);

  print_board(board, bsize);

  return 0;
}
