#include <bits/stdc++.h>
using namespace std;

map<int, vector<string> > keys = {
    {2, {"a", "b", "c"}},
    {3,  {"d", "e", "f"}},
    {4, {"g", "h", "i"}},
    {5, {"j", "k", "l"}},
    {6, {"m", "n", "o"}},
    {7, {"p", "q", "r", "s"}},
    {8, {"t", "u", "v"}},
    {9, {"w", "x", "y", "z"}}
};

vector<string> keypad(deque<int> nums) {
    vector<string> output;
    if (nums.size() == 1) {
        output = keys[nums[0]];
        return output;
    }

    deque<int> numsDeq = nums;
    numsDeq.pop_back();

    vector<string> interim = keypad(numsDeq);

    for (string key : keys[nums[nums.size() - 1]]) {
        vector<string> temp = interim;
        for (string x : temp) {
            x.append(key);
            output.push_back(x);
        }
    }
    return  output;
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
        int inputNum;
        cin >> inputNum;
        deque<int> pressed;
        int place = 1;
        while (inputNum / place) {
            pressed.push_front((inputNum / place) % 10);
            place *= 10;
        }

        vector<string> output = keypad(pressed);

        for (string x : output) {
            cout << x << endl;
        }
    }

    return 0;
}
