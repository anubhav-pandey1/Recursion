#include <bits/stdc++.h>
using namespace std;

#define ll long long int

string familyTree(ll n, ll K) {                                // Bottom-up recursion approach
    if (n == 1) {                                              // ft(n,K) -> ft(n-1, K/2) --> ft(n-2, K/4)
        return "Male\n";
    }

    if (familyTree(n - 1, ceil((float)K / 2)) == "Male\n") {   // If parent is male
        if (K % 2)
            return "Male\n";
        else
            return "Female\n";
    }
    else {                                                     // If parent is female
        if (K % 2)
            return "Female\n";
        else
            return "Male\n";
    }
}

// Can come up with a binary search or top-down recursion approach

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

// int main() {
// #ifndef ONLINE_JUDGE
//     freopen("input.txt", "r", stdin);
//     freopen("output.txt", "w", stdout);
// #endif
//     int t, count;
//     long long int k, num;
//     scanf("%d", &t);
//     while (t--)
//     {
//         count = 0;
//         scanf("%lld %lld", &k, &num);
//         if (num == 1)
//             printf("Male\n");
//         else if (num == 2)
//             printf("Female\n");
//         else {
//             num = num - 1;
//             while (num > 1)
//             {
//                 if (num % 2 != 0)
//                     count += 1;
//                 num = num / 2;
//             }
//             if (count % 2 == 0)
//                 printf("Female\n");
//             else
//                 printf("Male\n");
//         }
//         printf("\n");
//     }
//     return 0;
// }
