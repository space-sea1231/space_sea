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
const int N = 1e4 + 10;
const int K = 12;

int n, m, C;
ll f[N];
vector<pair<int, int> > q;

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m >> C;
    for (int i = 1; i <= n; i++) {
        int v, w, d;
        cin >> v >> w >> d;
        for (int j = 0; j < K; j++) {
            int t = (1 << j);
            if (d >= t) {
                d -= t;
                q.emplace_back(make_pair(v * t, w * t));
            }
        }
        if (d) q.emplace_back(make_pair(v * d, w * d));
    }
    for (int i = 1; i <= m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        for (int j = C; ~j; j--) {
            for (int k = 0; k <= j; k++) {
                f[j] = max(f[j], f[j - k] + (ll)a * k * k + b * k + c);
            }
        }
    }
    int len = q.size();
    for (pair<int, ll> cur:q) {
        for (int j = C; j >= cur.first; j--) {
            f[j] = max(f[j], f[j - cur.first] + cur.second);
        }
    }
    printf("%lld\n", f[C]);
    return 0;
}
/*
上三门为官，军爷戏子拐中仙，正如烟上月。
平三门曰贼，阎罗浪子笑面佛，正如杯中酒。
下三门经商，美人算子棋通天，正如花下风流。
*/