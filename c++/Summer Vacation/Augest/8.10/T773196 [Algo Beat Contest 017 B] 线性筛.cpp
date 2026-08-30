#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

typedef long long ll;
const int N = 1e6 + 10;

int n, LOGN;
int a[N], fen[N];

void add(int i, int v) {
    for (; i <= n; i += i & -i) fen[i] += v;
}
int kth(int k) {
    int pos = 0;
    for (int pw = LOGN; pw; pw >>= 1) {
        int nxt = pos + pw;
        if (nxt <= n && fen[nxt] < k) {
            pos = nxt;
            k -= fen[nxt];
        }
    }
    return pos + 1;
}

signed main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) {
        fen[i]++;
        int j = i + (i & -i);
        if (j <= n) fen[j] += fen[i];
    }
    LOGN = 1;
    while ((LOGN << 1) <= n) LOGN <<= 1;
    int len = n;
    int cb = 1;
    while ((ll)(cb + 1) * (cb + 1) * (cb + 1) <= len) cb++;
    vector<int> out;
    out.reserve(n + 30000);
    int cnt = 0;
    while (len > 0) {
        while ((ll)cb * cb * cb > len) cb--;
        int p[110];
        for (int j = 1; j <= cb; j++) p[j] = kth(j * j * j);
        for (int j = 1; j <= cb; j++) out.push_back(a[p[j]]);
        out.push_back(0);
        for (int j = 1; j <= cb; j++) add(p[j], -1);
        len -= cb;
        cnt++;
    }
    printf("%d\n", cnt);
    for (auto cur:out) {
        if (cur == 0) printf("\n");
        else  printf("%d ", cur);
    }
    return 0;
}