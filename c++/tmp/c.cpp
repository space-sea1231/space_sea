#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 6e6 + 10;
const int K = 60;
const int Mod = 998244353;

int n, Q;
int qp[K << 1];
vector<int> f[N];

namespace Trie {
    int num;
    int ch[N][2];
    int sum[N];

    void Insert(ll a) {
        int p = 0;
        sum[p]++;
        for (int i = K - 1; ~i; i--) {
            if (!ch[p][a >> i & 1]) ch[p][a >> i & 1] = ++num;
            p = ch[p][a >> i & 1];
            sum[p]++;
        }
    }
    void Solve(int u, int d) {
        f[u].resize(sum[u]);
        if (!d) return ;
        if (ch[u][0]) Solve(ch[u][0], d - 1);
        if (ch[u][1]) Solve(ch[u][1], d - 1);
        for (int i = 0; i < sum[ch[u][0]]; i++) f[u][i] = f[ch[u][0]][i];
        for (int i = sum[ch[u][0]]; i < sum[u]; i++) f[u][i] = ((ll)f[ch[u][1]][i - sum[ch[u][0]]] + qp[(d - 1 << 1)]) % Mod;
        for (int i = 0; i < sum[ch[u][1]]; i++) f[u][i] = ((ll)f[u][i] + f[f[ch[u][1]][i]]) % Mod;
        for (int i = sum[ch[u][1]]; i < sum[u]; i++) {
            f[u][i] = ((ll)f[u][i] + f[ch[u][0]][i - sum[u][1]]) % Mod;
            f[u][i] = ((ll)f[u][i] + qp[1 << d - 1]);
        }
    }
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> Q;
    for (int i = 1; i <= n; i++) {
        string a;
        cin >> a;
        Insert(a);
    }
    qp[0] = 1;
    for (int i = 1; i < (K << 1); i++) qp[i] = (ll)qp[i - 1] * 2 % Mod;
    Solve(1, K);
    return 0;
}
/*
Old streets hold wormest stories
老街藏着最暖的故事
*/