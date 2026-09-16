#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <deque>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const ll INF = 1e18 + 1;
const int N = 1.5e5 + 10;

int n, m, d;
ll f[N][2];

struct Node {
    int a, b, t;
    bool operator<(const Node &s) const {return t < s.t;}
}; Node node[N];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m >> d;
    // for (int i = 1; i <= n; i++) f[i][0] = f[i][1] = -INF;
    for (int i = 1; i <= m; i++) cin >> node[i].a >> node[i].b >> node[i].t;
    sort(node + 1, node + m + 1);
    deque<int> q;
    bool flag = false;
    for (int i = 1; i <= n; i++) f[i][flag ^ 1] = node[1].b - abs(node[1].a - i);
    for (int i = 2; i <= m; i++) {
        q.clear();
        int lst = 0;
        for (int j = 1; j <= n; j++) {
            int l = (int)max(1LL, j - (ll)(node[i].t - node[i - 1].t) * d);
            int r = (int)min((ll)n, j + (ll)(node[i].t - node[i - 1].t) * d);
            while (!q.empty() && q.front() < l) q.pop_front();
            for (int k = lst + 1; k <= r; k++) {
                while (!q.empty() && f[q.back()][flag ^ 1] < f[k][flag ^ 1]) q.pop_back();
                q.push_back(k);
            }
            lst = r;
            f[j][flag] = f[q.front()][flag ^ 1] + node[i].b - abs(node[i].a - j);
        }
        flag ^= 1;
    }
    ll ans = -INF;
    for (int i = 1; i <= n; i++) ans = max(ans, f[i][flag ^ 1]);
    printf("%lld\n", ans);
    return 0;
}
/*
curiosity 好奇
ordinary 日常的
brand new 焕然一新
*/