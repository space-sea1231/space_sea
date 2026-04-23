#include <iostream>
#include <stdio.h>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;
typedef long double ld;

const int N = 1e5 + 10;
const int M = 3e6 + 10;


int t, n, m, k;
int sum[N];
ld f[N];
int q[N], p[N];
int pre[N];
string s[N];

ld Pow(ld a, int b) {
    ld sum = 1;
    while (b) {
        if (b & 1) sum = sum * a;
        a = a * a;
        b >>= 1;
    }
    return sum;
}

ld Calc(int x, int y) {
    return f[y] + Pow(abs(sum[x] - sum[y] - m), k);
}

int Bound(int x, int y) {
    int l = x, r = n + 1;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (Calc(mid, x) >= Calc(mid, y)) r = mid;
        else l = mid + 1;
    }
    return l;
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> t;
    while (t--) {
        cin >> n >> m >> k;
        m++;
        for (int i = 1; i <= n; i++) {
            cin >> s[i];
            sum[i] = sum[i - 1] + s[i].length() + 1;
        }
        int head = 1, tail = 1;
        q[1] = 0;
        for (int i = 1; i <= n; i++) {
            while (head < tail && p[head] <= i) head++;
            f[i] = Calc(i, q[head]);
            pre[i] = q[head];
            while (head < tail && p[tail - 1] >= Bound(q[tail], i)) tail--;
            p[tail] = Bound(q[tail], i);
            q[++tail] = i;
        }
        if (f[n] > 1e18) printf("Too hard to arrange\n");
        else {
            printf("%.0Lf\n", f[n]);
            // for (int i = n; i; i = pre[i]) q[++tail] = i;
            q[0] = n, tail = 0;
            for(int i = n; i; q[++tail] = i = pre[i]);
            for (; tail; tail--) {
                for (int i = q[tail] + 1; i < q[tail - 1]; i++) printf("%s ", s[i].c_str());
                printf("%s\n", s[q[tail - 1]].c_str());
            }
        }
        printf("--------------------\n");
    }
    return 0;
}