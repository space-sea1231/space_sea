#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cmath>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e6 + 10;
const int M = 1e7 + 10;
const int Mod = 998244353;

int n, m;
int cnt, siz;
int ans[N];
int prime[M], pos[M], inv[M];
bool vis[M];
int vec[N][11], top[N];

int read() {
    char c = getchar();
    int flag = 1;
    while (c < '0' || c > '9') {
        if (c == '-') flag = -1;
        c = getchar();
    }
    int sum = 0;
    while ('0' <= c && c <= '9') {
        sum = (sum << 3) + (sum << 1) + (c ^ 48);
        c = getchar();
    }
    return sum * flag;
}
int Pow(int a, int b) {
    int sum = 1;
    while (b) {
        if (b & 1) sum = (ll)sum * a % Mod;
        a = (ll)a * a % Mod;
        b >>= 1;
    }
    return sum;
}
void Prime() {
    for (int i = 2; i <= 5000; i++) {
        if (!vis[i]) {
            prime[++cnt] = i;
            pos[i] = cnt;
            inv[cnt] = Pow(i, Mod - 2);
        }
        for (int j = 1; j <= cnt && i * prime[j] <= 5000; j++) {
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0) break;
        }
    }
}

namespace Mo {
    int cur = 1;
    int tot[M];

    struct Query {
        int l, r;
        int id;

        bool operator<(const Query &s) const {
            if (l / siz != s.l / siz) return l < s.l;
            return (l / siz & 1 ? r > s.r : r < s.r);
        }
    }; Query qry[N];

    void Add(int p) {
        // cerr << q[p].size() << "\n";
        for (int i = 1; i <= top[p]; i++) {
            if (!tot[vec[p][i]]) cur = (ll)cur * prime[vec[p][i]] % Mod;
            tot[vec[p][i]]++;
            // cerr << v << " " << cur << "\n";
        }
    }
    void Del(int p) {
        // cerr << q[p].size() << "\n";
        for (int i = 1; i <= top[p]; i++) {
            tot[vec[p][i]]--;
            if (!tot[vec[p][i]]) cur = (ll)cur * inv[vec[p][i]] % Mod;
        }
    }
} using namespace Mo;
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    n = read();
    siz = sqrt(n);
    Prime();
    for (int i = 1; i <= n; i++) {
        int a = read();
        for (int j = 1; j <= cnt && prime[j] * prime[j] <= a; j++) {
            if (a % prime[j] == 0) {
                // if (i == 1) cerr << pos[prime[j]] << " ";
                vec[i][++top[i]] = pos[prime[j]];
                a /= prime[j];
                while (a % prime[j] == 0) a /= prime[j];
                // printf("Debug:%d(%d) has prime %d\n", i, a[i], prime[j]);
            }
        }
        // if (a != 1 && i == 1) cerr << pos[a] << " ";
        if (a != 1) vec[i][++top[i]] = pos[a];
    }
    m = read();
    for (int i = 1; i <= m; i++) {
        qry[i].l=read();
        qry[i].r=read();
        qry[i].id = i;
    }
    sort(qry + 1, qry + m + 1);
    int L = 1, R = 0;
    double st = clock();
    for (int i = 1; i <= m; i++) {
        while (L > qry[i].l) Add(--L);
        while (R < qry[i].r) Add(++R);
        while (L < qry[i].l) Del(L++);
        while (R > qry[i].r) Del(R--);
        ans[qry[i].id] = cur;
    }
    double ed = clock();
    double tim = (ed - st) / 1000000;
    cerr << "Time: " << tim << "\n";
    for (int i = 1; i <= m; i++) printf("%d\n", ans[i]);
    return 0;
}