#include <bits/stdc++.h>
using namespace std;

int uniquePath(int m, int n) {
    if (m == 1 || n == 1) {
        return 1;
    }
    return uniquePath(m - 1, n) + uniquePath(m, n - 1);
}

int main() {
    cout << uniquePath(9, 15) << endl;
    return 0;
}
