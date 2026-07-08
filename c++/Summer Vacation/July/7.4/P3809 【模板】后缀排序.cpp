#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e6 + 10;

int n, m = 122;
char s[N];
int x[N], y[N];
int cnt[N], sa[N];
// sa->排名第i的后缀起始位置
// x->后缀起始位置为i的排名
// y->第二关键字排名为i的起始位置
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> (s + 1);
    n = strlen(s + 1);
    for (int i = 1; i <= n; i++) {
        x[i] = s[i];
        cnt[x[i]]++;
    }
    for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
    for (int i = n; i >= 1; i--) sa[cnt[x[i]]--] = i;
    for (int k = 1; k <= n; k <<= 1) {
        int num = 0;
        for (int i = n - k + 1; i <= n; i++) y[++num] = i;
        for (int i = 1; i <= n; i++) if (sa[i] > k) y[++num] = sa[i] - k;
        for (int i = 1; i <= m; i++) cnt[i] = 0;
        for (int i = 1; i <= n; i++) cnt[x[i]]++;
        for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
        for (int i = n; i >= 1; i--) {
            sa[cnt[x[y[i]]]--] = y[i];
            y[i] = 0;
        }
        swap(x, y);
        num = 1, x[sa[1]] = 1;
        for (int i = 2; i <= n; i++) {
            if (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) x[sa[i]] = num;
            else x[sa[i]] = ++num;
        }
        if (num == n) break;
        m = num;
    }
    for (int i = 1; i <= n; i++) printf("%d ", sa[i]);
    return 0;
}