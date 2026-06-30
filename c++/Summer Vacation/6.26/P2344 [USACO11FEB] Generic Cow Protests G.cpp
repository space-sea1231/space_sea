#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 1e5 + 10;
const int Mod = 1e9 + 9;

int n;
int a[N], f[N];
int tmp[N], tot[N];

namespace BinaryTree {
    ll sum[N];

    int Lowbit(int x) {
        return x & (-x);
    }
    void Add(int pos, int val) {
        for (int i = pos; i <= n; i += Lowbit(i)) sum[i] = (sum[i] + val) % Mod;
    }
    ll Query(int pos) {
        ll rev = 0;
        for (int i = pos; i > 0; i -= Lowbit(i)) rev = (rev + sum[i]) % Mod;
        return rev;
    }
} using namespace BinaryTree;

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    int len = 0;
    tmp[++len] = tot[0];
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        tot[i] = tot[i - 1] + a[i];
        tmp[++len] = tot[i];
    }
    sort(tmp + 1, tmp + len + 1);
    len = unique(tmp + 1, tmp + len + 1) - tmp - 1;
    for (int i = 0; i <= n; i++) tot[i] = lower_bound(tmp + 1, tmp + len + 1, tot[i]) - tmp;
    Add(tot[0], f[0] = 1);
    for (int i = 1; i <= n; i++) {
        f[i] = Query(tot[i]);
        Add(tot[i], f[i]);
    }
    printf("%lld\n", f[n]);
    return 0;
}