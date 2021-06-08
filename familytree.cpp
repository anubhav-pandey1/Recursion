#include <bits/stdc++.h>
using namespace std;

#define ll long long int

string familyTree(ll n, ll K) {
    if (n == 1) {
        return "Male\n";
    }

    if (familyTree(n - 1, ceil((float)K / 2)) == "Male\n") {
        if (K % 2)
            return "Male\n";
        else
            return "Female\n";
    }
    else {
        if (K % 2)
            return "Female\n";
        else
            return "Male\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    ll testNum;
    cin >> testNum;
    while (testNum--) {
        ll n;
        ll K;
        cin >> n;
        cin >> K;

        cout << familyTree(n, K) << endl;
    }

    return 0;
}
