#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
// #define int long long

using namespace std;
typedef long long ll;

const int N = 10;

int t, n, m;
int a[N];
int q[8] = {0, 5, 7, 9, 11, 13, 16, 17};

int Exgcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    int d = Exgcd(b, a % b, x, y);
    int z = x; x = y; y = z - y * (a / b);
    return d;
}

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> t >> n >> m;
    while (t--) {
        for (int i = 1; i <= 7; i++) a[i] = 0;
        int acc = 1;
        for (int i = 1; i <= 7; i++) {
            for (int j = 1; j <= 18; j++) printf("%d ", q[i]);
            printf("\n");
            fflush(stdout);
            for (int j = 1; j <= 18; j++) {
                int tmp;
                cin >> tmp;
                if (tmp == -1) exit(0);
                a[i] = (a[i] + tmp) % q[i];
            }
            acc *= q[i];
        }
        int ans = 0;
        for (int i = 1; i <= 7; i++) {
            int x, y;
            int d = Exgcd(acc / q[i], q[i], x, y);
            x = (x % (q[i] / d) + (q[i] / d)) % (q[i] / d);
            ans = (ans + acc / q[i] * x * a[i]) % acc;
        }
        printf("%d\n", ans);
        fflush(stdout);
        int rev;
        cin >> rev;
        if (rev == -1) exit(0);
    }

    return 0;
}