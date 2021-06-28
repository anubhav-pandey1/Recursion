#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> subsetsWithDup(vector<int>& v) {
    sort(v.begin(), v.end());
    vector<vector<int>> output;
    if (v.empty()) {
        output.push_back({});
        return output;
    }

    int last = v[v.size() - 1];
    v.pop_back();
    vector<vector<int>> interim = subsetsWithDup(v);

    for (int r = 0; r < interim.size(); r++) {
        vector<int> row = interim[r];
        output.push_back(row);
        row.push_back(last);
        output.push_back(row);
    }
    set<vector<int>> temp(output.begin(), output.end());
    vector<vector<int>> result(temp.begin(), temp.end());
    return result;
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
        int size;
        cin >> size;
        vector<int> v;
        for (int i = 0; i < size; i++) {
            int ele;
            cin >> ele;
            v.push_back(ele);
        }

        vector<vector<int>> result = subsetsWithDup(v);
        // cout << "Size of result: " << result.size() << endl;
        for (int r = 0; r < result.size(); r++) {
            if (result[r].empty()) {
                cout << "-" << endl;
                continue;
            }
            for (int c = 0; c < result[r].size(); c++) {
                cout << result[r][c] << " ";
            }
            cout << endl;
        }
        cout << "..............." << endl;
    }

    return 0;
}

// Test cases:

// Inputs:

// 3
// 1
// 1
// 3
// 1 2 3
// 1
// 5
// 4 4 4 1 4

// Outputs (order can be different):

// -
// 1
// ...............
// -
// 1
// 1 2
// 1 2 3
// 1 3
// 2
// 2 3
// 3
// ...............
// -
// 1
// 1 4
// 1 4 4
// 1 4 4 4
// 1 4 4 4 4
// 4
// 4 4
// 4 4 4
// 4 4 4 4
// ...............
