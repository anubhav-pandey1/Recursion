#include <bits/stdc++.h>
using namespace std;

#define ll long long int

string familyTree(ll n, ll K) {                                // Bottom-up recursion approach
    if (n == 1) {                                              // ft(n,K) -> ft(n-1, K/2) --> ft(n-2, K/4)
        return "Male";
    }

    if (familyTree(n - 1, ceil((float)K / 2)) == "Male") {     // If parent is male
        if (K % 2)                                             // Odd child is male, even child female
            return "Male";                                     // Ceil(K/2) gives K-value for parent
        else                                                   // Recursion to find gender of parent
            return "Female";
    }
    else {                                                     // If parent is female
        if (K % 2)                                             // Odd child is female, even child male
            return "Female";
        else
            return "Male";
    }
}

// Can come up with a binary search or top-down recursion approach

string family_tree(ll n, ll K, string rootGender = "Male") {   // Top-down recursion approach
    if (n == 1) {                                              // Still ft(n, K) -> ft(n-1, K)
        return rootGender;
    }

    ll numChildrenGen = 1LL << (n - 1);                        // Calculating pow(2, n - 1)
    if (K <= numChildrenGen / 2) {                             // If we go left from the parent for new subtree
        return family_tree(n - 1, K, rootGender);              // New root gender remains same for new subtree
    }                                                          // K also remains same since it falls in first half
    else {                                                     // Else if we go right since K > numChildrenGen/2
        string newRootGender = "Male";                         // If parent gender = F then subtree parent gender = M
        if (rootGender == "Male") {                             // If parent gender = M then subtree parent gender = F
            newRootGender = "Female";                          // This is because we are going right
        }                                                      // K needs to be re-index to start from K/2 + 1
        return family_tree(n - 1, K - numChildrenGen / 2, newRootGender);
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
