#include <bits/stdc++.h>
using namespace std;

bool checkCell(vector<vector<int>>& mz, int r, int c, char move) {
    int n = mz.size();
    switch (move) {
    case 'D' :
        if ((r + 1) < n && mz[r + 1][c] == 1) {
            return true;
        }
        break;
    case 'R' :
        if ((c + 1) < n && mz[r][c + 1] == 1) {
            return true;
        }
        break;
    case 'U' :
        if ((r - 1) >= 0 && mz[r - 1][c] == 1) {
            return true;
        }
        break;
    case 'L' :
        if ((c - 1) >= 0 && mz[r][c - 1] == 1) {
            return true;
        }
        break;
    default:
        break;
    }
    return false;
}

void mazePath(vector<vector<int>>& mz, vector<string>& output, string& path, int r, int c) {
    int n = mz.size();
    if (r == (n - 1) && c == (n - 1)) {
        output.push_back(path);
        path.pop_back();
        mz[r][c] = 1;
        return;
    }

    mz[r][c] = 0;
    vector<char> dirs = {'D', 'R', 'U', 'L'};
    for (char& dir : dirs) {
        if (checkCell(mz, r, c, dir)) {
            path.push_back(dir);
            switch (dir) {
            case 'D' :
                mazePath(mz, output, path, r + 1, c);
                break;
            case 'R' :
                mazePath(mz, output, path, r, c + 1);
                break;
            case 'U' :
                mazePath(mz, output, path, r - 1, c);
                break;
            case 'L' :
                mazePath(mz, output, path, r, c - 1);
                break;
            default:
                break;
            }
        }
    }
    mz[r][c] = 1;
    if (!path.empty())
        path.pop_back();
}

vector<string> findPath(vector<vector<int>>& mz, int n) {
    if (mz[0][0] == 0) {
        return {"-1"};
    }
    vector<string> output;
    string path;
    mazePath(mz, output, path, 0, 0);
    sort(output.begin(), output.end());
    return output;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int testNum;
    cin >> testNum;
    while (testNum--) {
        int n;
        cin >> n;
        vector<vector<int>> maze;
        for (int r = 0; r < n; r++) {
            vector<int> row;                                    // Can also have int based inputs, just include spaces in inputs
            string line;
            cin >> line;
            for (int c = 0; c < n; c++) {
                int cell = line[c] - '0';
                row.push_back(cell);
            }
            maze.push_back(row);
        }

        // for (int r = 0; r < n; r++) {                        // Test for bounding function
        //     for (int c = 0; c < n; c++) {
        //         cout << checkCell(maze, r, c, 'L') << " ";
        //     }
        //     cout << endl;
        // }

        vector<string> result = findPath(maze, n);
        for (string& s : result) {
            cout << s << endl;
        }
        cout << "_________________" << endl;
    }
    return 0;
}

// Test cases:

// Inputs:
