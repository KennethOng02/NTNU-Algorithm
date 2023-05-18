#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class CorgiBall {
    int ball_num, shot_num;
    vector<int> sequence;

    public:
        CorgiBall(int ball_num, int shot_num) {
            this->ball_num = ball_num;
            this->shot_num = shot_num;
        }

        void get_sequence() {
            int temp;
            for(int i = 0; i < shot_num; i++) {
                cin >> temp;
                sequence.push_back(temp);
            }
        }
        
        void print_sequence() {
            for(int i = 0; i < shot_num; i++) {
                cout << sequence[i] << ' ';
            }
            cout << '\n';
        }
        
        int find_min_group() {
            /*
            2 7 8 11 15 1 3 10 13 14 4 6 12 5 9

            2 7 8 11 15
            1 3 10 13 14
            4 6 12
            5 9
            */
            vector<vector<int>> groups;
            groups.push_back(vector<int>());
            groups[0].push_back(sequence[0]);
            int j = 1;
            for(int i = 1; i < sequence.size(); i++) {
                if(sequence[i] < sequence[i - 1]) {
                    j++;
                    groups.push_back(vector<int>());
                }
                groups[j - 1].push_back(sequence[i]);
            }
            
            /*
            1  2  3  4  5  6  7  8  9 10 11 12 13 14 15
            1  0  1  2  3  2  0  0  3  1  0  2  1  1  0
            */
            vector<int> ball_group(ball_num + 1, -1);
            for(int i = 0; i < groups.size(); i++) {
                for(int j = 0; j < groups[i].size(); j++) {
                    ball_group[groups[i][j]] = i;
                }
            }

            /*
             1  2  3  4  5  6  7  8  9  10  11  12  13  14  15
            -1 -1  1 -1 -1  4  2  7  5   3   8   6  10  13  11
            */
            vector<int> prev(ball_num + 1, -1);
            for(int i = 1; i < shot_num; i++) {
                if(sequence[i - 1] < sequence[i])                
                    prev[sequence[i]] = sequence[i - 1];
            }

            int currGroup = 1;
            vector<int> grp(ball_num + 1);
            for(int i = 1; i <= ball_num; i++) {
                if(ball_group[i] == -1)
                    continue;

                if(prev[i] == -1)
                    grp[i] = currGroup;
                else
                    grp[i] = max(grp[prev[i]] + 1, currGroup);
                currGroup = grp[i];
            }

            if(shot_num > 3 && (sequence.rbegin()[2] < sequence.rbegin()[0]) && (sequence.rbegin()[0] < sequence.rbegin()[1]) && (sequence.rbegin()[2] < sequence.rbegin()[1])) {
                int second_last = sequence.rbegin()[1];
                int last = sequence.rbegin()[0];
                if(grp[last] == grp[second_last])
                    currGroup++;
            }

            return currGroup;
        }
};

void fast_io() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
}

int main() {
    fast_io();

    int ball_num, shot_num;

    cin >> ball_num >> shot_num;
    
    CorgiBall cb(ball_num, shot_num);

    cb.get_sequence();

    cout << cb.find_min_group() << '\n';

    return 0;
}
