#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

class Surface {
    int row, col;
    char** room;
    int br, bc, dr, dc;
    int row_list[4] = {-1, 1, 0, 0};
    int col_list[4] = {0, 0, -1, 1};
    
    public:
        Surface(int row, int col) {
            this->row = row;
            this->col = col;
            room = new char*[row];
            for(int i = 0; i < row; i++) {
                room[i] = new char[col];
            }
        }

        void get_floor() {
            for(int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++) {
                    cin >> room[i][j];
                }
            }
        }

        void print_floor() {
            for(int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++) {
                    cout << room[i][j] << ' ';
                }
                cout << '\n';
            }
            cout << '\n';
        }
        
        int escape_path_available(vector<vector<int>> time, int timestamp) {
            queue<pair<int, int>> q;
            q.push({br, bc});
        
            int x, y, i, delta_x, delta_y;
            while(!q.empty()) {
                x = q.front().first;
                y = q.front().second;
                
                if(x == dr && y == dc)
                    return 1;
                
                for(i = 0; i < 4; i++) {
                    delta_x = x + row_list[i];
                    delta_y = y + col_list[i];
                    
                    if(delta_x < 0 || delta_x >= row || delta_y < 0 || delta_y >= col || time[delta_x][delta_y] <= timestamp)
                        continue;

                    time[delta_x][delta_y] = -1;

                    q.push({delta_x, delta_y});
                }
                q.pop();
            }
            return 0;
        }
        
        int get_escape_time() {
            queue<pair<int, int>> q;
            for(int i = 0; i < row; i++) {
                for(int j = 0; j < col; j++) {
                    if(room[i][j] == 'L') {
                        q.push({i, j});
                    }else if(room[i][j] == 'B') {
                        br = i;
                        bc = j;
                    }else if(room[i][j] == 'D') {
                        dr = i;
                        dc = j;
                    }
                }
            }

            vector<vector<int>> time(row, vector<int>(col, 0));
            int x, y, delta_x, delta_y;
            int max_time = 0;
            while(!q.empty()) {
                x = q.front().first;
                y = q.front().second;
                
                for(int i = 0; i < 4; i++) {
                    delta_x = x + row_list[i];
                    delta_y = y + col_list[i];
                    
                    if(delta_x < 0 || delta_x >= row || delta_y < 0 || delta_y >= col || room[delta_x][delta_y] != 'C') // only from to 'C
                        continue;

                    room[delta_x][delta_y] = 'L';

                    time[delta_x][delta_y] = time[x][y] + 1;

                    if(time[delta_x][delta_y] > max_time)
                        max_time = time[delta_x][delta_y];

                    q.push({delta_x, delta_y});
                }
                q.pop();
            }
            time[dr][dc] = INT_MAX;
            
            // binary search
            int low = 0;
            int high = max_time;
            int mid;
            int flag = 0;
            while(low <= high) {
                mid = (low + high) / 2;
                int path_available = escape_path_available(time, mid); 
                if(path_available) {
                    low = mid + 1;
                    flag = 0;
                }else {
                    high = mid - 1; 
                    flag = 1;
                }
            }

            if(flag)
                mid--;

            return mid ? mid : -1;
        }
};

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
}

int main() {
    fast_io();

    int row, col;
    cin >> row >> col;
    
    Surface s(row, col);

    s.get_floor();

    cout << s.get_escape_time() << '\n';

    return 0;
}