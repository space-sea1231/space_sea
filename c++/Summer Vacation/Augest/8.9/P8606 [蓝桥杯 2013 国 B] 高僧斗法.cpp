#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e2 + 10;

int n;
int a[N], b[N];

// bool Check() {
//     int rev = 0;
//     for (int i = 1; i < n; i += 2) rev ^= b[i];
//     return rev == 0;
// }
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    int sum_xor = 0;
    while (cin >> a[++n]); n--;
    for (int i = 1; i < n; i++) {
        b[i] = a[i + 1] - a[i] - 1;
        if (i % 2) sum_xor ^= b[i];
    }
    // cerr<<sum_xor<<endl;
    if (sum_xor == 0) {printf("-1\n"); return 0;}
    // if (Check()) {printf("-1\n"); return 0;}
    for (int i = 1; i < n; i++) {
        sum_xor ^= b[i - ((i & 1) == 0)];
        for (int j = 1; j <= b[i]; j++) {
            // if (i == 1) cerr<<sum_xor<< " " << (sum_xor ^ (b[i] - j)) << endl;
            if (i & 1 && (sum_xor ^ (b[i] - j)) == 0) {
                printf("%d %d\n", a[i], a[i] + j);
                return 0;
            }
            else if ((i & 1) == 0 && (sum_xor ^ (b[i - 1] + j)) == 0) {
                printf("%d %d\n", a[i], a[i] + j);
                return 0;
            }
            // if (i & 1) {
            //     b[i] -= j;
            //     if (Check()) {
            //         printf("%d %d\n", a[i], a[i] + j);
            //         return 0;
            //     }
            //     b[i] += j;
            // }
            // else {
            //     b[i - 1] += j;
            //     if (Check()) {
            //         printf("%d %d\n", a[i], a[i] + j);
            //         return 0;
            //     }
            //     b[i - 1] -= j;
            // }
        }
        sum_xor ^= b[i - ((i & 1) == 0)];
    }
    return 0;
}