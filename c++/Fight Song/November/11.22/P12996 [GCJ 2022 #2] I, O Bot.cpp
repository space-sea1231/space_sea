#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#define int long long
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const ll INF = 1e18 + 1;
const int N = 1e5 + 10;

int T;
int n, c;
ll dp[N], g[N][2];
int f[N];
int lst[N << 1];

struct Node {
    int x;
    bool s;

    bool operator<(const Node &s) const {
        return x < s.x;
    }
}; 
vector<Node> q[2];

void Solve(int cur) {
    cin >> n >> c;
    q[0].clear(), q[1].clear();
    for (int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;
        q[x < 0].emplace_back((Node){(x < 0 ? -1 : 1) * x, y});
    }
    ll ans = 0;
    for (int i = 0; i <= 1; i++) {
        sort(q[i].begin(), q[i].end());
        int k = -1;
        for (int j = 0, lim = q[i].size(); j <= lim; j++) {
            dp[j] = INF;
            lst[j] = lst[j + lim + 1] = -1;
        }
        dp[0] = 0;
        lst[q[i].size() + 1] = 0;
        for (int j = 0, lim = q[i].size(); j < lim; j++) {
            // cerr << j << " " << q[i][j].x << "\n";
            f[j + 1] = f[j] + (q[i][j].s == 1 ? 1 : -1);
            g[j + 1][0] = g[j][0] + (q[i][j].s == 0 ? q[i][j].x : 0);
            g[j + 1][1] = g[j][1] + (q[i][j].s == 1 ? q[i][j].x : 0);
            dp[j + 1] = min(dp[j + 1], dp[j] + (ll)2 * q[i][j].x);
            // cerr << dp[j] << " " << dp[j + 1] << " " << 2 * q[i][j].x << "\n";
            if (j > 0) {
                // cerr << "Debug1:\n";
                dp[j + 1] = min(dp[j + 1], dp[j - 1] + (ll)2 * q[i][j].x + (q[i][j].s == q[i][j - 1].s) * c);
            }
            if (lst[f[j + 1] + lim + 1] >= 0) {
                // cerr << "Debug2:\n";
                dp[j + 1] = min(dp[j + 1], dp[lst[f[j + 1] + lim + 1]] + (ll)2 * (g[j + 1][q[i][j].s] - g[lst[f[j + 1] + lim + 1]][q[i][j].s]));
            }
            lst[f[j + 1] + lim + 1] = j + 1;
        }
        for (int j = 0, lim = q[i].size(); j < lim; j++) {
            // printf("g[%d][0]=%d g[%d][1]=%d\n", j + 1, g[j + 1][0], j + 1, g[j + 1][1]);
            // printf("dp[%d]=%d\n", j + 1, dp[j + 1]);
        }
        // cerr << dp[q[i].size()] << "\n";
        ans += dp[q[i].size()];
    }
    printf("Case #%d: %lld\n", cur, ans);
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> T;
    for (int _ = 1; _ <= T; _++) Solve(_);
    return 0;
}
/*
🌌 星空知识卡片 05：昴星团（Pleiades / M45）

【📍 基础档案】

坐标：金牛座，中国星名“昴宿”（西方白虎七宿之一），距地球约 444 光年。

视星等：整团约 1.6 等；肉眼通常能看到 6 颗，视力好的能数出 7–9 颗。

类型：疏散星团，年龄仅约 1 亿年，成员大多是蓝白色 B 型星，总数超过 1000 颗。

【📖 文科浪漫与神话】

在希腊神话里，它们是“七姐妹”普勒阿得斯，被猎人俄里翁一路追赶，宙斯把她们放到天上避难。
所以今天猎户座升起时，昴星团总在前面“逃跑”，这场追逐已经跑了几千年。
日本叫它「すばる」，斯巴鲁车标上的六颗星就是它。
中国古人则把昴星团当作“视力测试题”：能数出几颗，就是衡量眼力的标准。

【🔭 硬核数据与物理】

同班同学：团里的星诞生于同一片分子云，年龄和成分几乎一样，像一群同年入学的孩子；
大约 2.5 亿年后，它们会被银河的潮汐拉散，各奔东西。

蓝色不是冰：照片里那层朦胧的蓝雾是反射星云：尘埃反射星光，本身不发光。

【🧭 观测指南】

怎么找：先找金牛座的 V 形（亮星毕宿五是 V 形的一角），
沿 V 形的上方向西北延伸，会看到一小团“挤在一起的星星”，像一小把碎钻。

用双筒望远镜看最惊艳：肉眼看到的一小团，会展开成几十颗蓝白星。这是城市里最容易得到的“哇”。
*/