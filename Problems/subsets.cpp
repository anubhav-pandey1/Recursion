#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> subsets(vector<int>& v) {
    vector<vector<int>> output;
    if (v.size() == 1) {
        output.push_back(v);
        output.push_back({});
        return output;
    }

    int last = v[v.size() - 1];
    v.pop_back();
    vector<vector<int>> interim = subsets(v);

    for (int r = 0; r < interim.size(); r++) {
        vector<int> row = interim[r];
        output.push_back(row);
        row.push_back(last);
        output.push_back(row);
    }
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
        int size;
        cin >> size;
        vector<int> v;
        for (int i = 0; i < size; i++) {
            int ele;
            cin >> ele;
            v.push_back(ele);
        }

        vector<vector<int>> result = subsets(v);
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
        cout << "---------" << endl;
    }

    return 0;
}

// Test cases:

// Inputs:

// 2
// 1
// 1
// 3
// 1 2 3

// Outputs (order can be different):

// 1
// -
// ---------
// 1
// 1 3
// 1 2
// 1 2 3
// -
// 3
// 2
// 2 3
// ---------
