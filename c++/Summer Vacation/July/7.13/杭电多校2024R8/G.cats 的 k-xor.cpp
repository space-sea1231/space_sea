#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int K = 1e6;
const int M = 50;

int cnt[M][4];
int tot, ans;
int t;
int a, b, c;
bool flag;
// int Pow(int a, int b) {
//     int sum = 1;
//     while (b) {
//         if (b & 1) sum = sum * a;
//         a = a * a;
//         b >>= 1;
//     }
//     return sum;
// }
void Get(int k, int x, int pos) {
    int sumk = 1, tmp = 0;
    while ((ll)sumk * k <= x) {
        sumk *= k;
        tmp++;
    }
    // cerr<<sumk<<" ";
    for (int i = tmp; i >= 0; i--) {
        if (x >= sumk) {
            cnt[i][pos] = x / sumk;
            x = x - sumk * (x / sumk);
        }
        sumk /= k;
    }
    tot = max(tmp, tot);
}
void Check(int k) {
    tot = 0, flag = true;
    // cerr<< "id=" << i<< endl;
    Get(k, a, 1), Get(k, b, 2), Get(k, c, 3);
    // cerr<<endl;
    for (int i = tot; i >= 0; i--) {
        // printf("k=%d %d %d %d\n", k, cnt[i][1], cnt[i][2], cnt[i][3]);
        if ((cnt[i][1] + cnt[i][2]) % k != cnt[i][3]) {
            flag = false;
        }
        cnt[i][1] = cnt[i][2] = cnt[i][3] = 0; 
    }
    // printf("\n");
    if (flag) {
        ans++;
        // cerr<<k<<" ";
    }
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> t;
    while (t--) {
        cin >> a >> b >> c;
        if (a + b < c) {
            printf("0\n");
            continue;
        }
        if (a + b == c) {
            printf("-1\n");
            continue;
        }
        int d = a + b - c;
        ans = 1;
        for (int i = 2; i * i <= d; i++) {
            if (d % i == 0) {
                Check(i);
                if (i * i != d) Check(d / i);
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}