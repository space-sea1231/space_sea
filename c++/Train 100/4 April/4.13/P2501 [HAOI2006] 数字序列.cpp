#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 3.5e4;
const int INF = 0x3f3f3f3f;

int n;
ll a[N], b[N], f[N];
int tail[N], len[N];
ll suml[N], sumr[N];
vector<int> v[N];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) b[i] = a[i] - i;
    int top = 0;
    b[n + 1] = INF;
    for (int i = 1; i <= n + 1; i++) {
        int pos = upper_bound(tail + 1, tail + top + 1, b[i]) - tail;
        if (pos > top) tail[++top] = b[i];
        else tail[pos] = b[i];
        len[i] = pos;
        v[len[i]].emplace_back(i);
    }
    printf("%d\n", n - top + 1);
    memset(f, 0x3f, sizeof(f));
    f[0] = 0, b[0] = -INF;
    v[0].emplace_back(0);
    for (int i = 1; i <= n + 1; i++) {
        for (int j:v[len[i] - 1]) {
            if (j > i || b[j] > b[i]) continue;
            suml[j] = 0;
            for (int k = j + 1; k < i; k++) suml[k] = suml[k - 1] + abs(b[k] - b[j]);
            sumr[i] = 0;
            for (int k = i - 1; k > j; k--) sumr[k] = sumr[k + 1] + abs(b[k] - b[i]);
            for (int k = j; k < i; k++) f[i] = min(f[i], f[j] + suml[k] + sumr[k + 1]);
        }
    }
    printf("%lld\n", f[n + 1]);
    return 0;
}