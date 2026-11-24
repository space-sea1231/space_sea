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

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e5 + 10;
const int K = 16;
const int Mod = 1e9 + 7;

int T;
int n;
int f[N], g[N][K + 1], d[N][K + 1];
int sg1[K], sg2[K], sc1[K], scg1[K], scg2[K];
vector<int> e[N];

void Dfs(int u, int fa) {
    for (int v : e[u]) {
        if (v == fa) continue;
        Dfs(v, u);
    }
    int s0 = 1, sd0 = 0;
    for (int k = 0; k < K; k++) sg1[k] = sg2[k] = sc1[k] = scg1[k] = scg2[k] = 0;
    for (int v : e[u]) {
        if (v == fa) continue;
        sd0 = (sd0 * f[v] + s0 * d[v][0]) % Mod;
        for (int k = 0; k < K; k++) {
            scg2[k] = (scg2[k] * f[v] + scg1[k] * g[v][k] + sg2[k] * d[v][k + 1]) % Mod;
            scg1[k] = (scg1[k] * f[v] + sc1[k] * g[v][k] + sg1[k] * d[v][k + 1]) % Mod;
            sc1[k] = (sc1[k] * f[v] + s0 * d[v][k + 1]) % Mod;
            sg2[k] = (sg2[k] * f[v] + sg1[k] * g[v][k]) % Mod;
            sg1[k] = (sg1[k] * f[v] + s0 * g[v][k]) % Mod;
        }
        s0 = s0 * f[v] % Mod;
    }
    g[u][0] = s0;
    f[u] = (s0 + sd0) % Mod;
    for (int k = 0; k < K; k++) {
        g[u][k + 1] = sg2[k];
        d[u][k] = (sg1[k] + scg1[k]) % Mod;
        f[u] = (f[u] + g[u][k + 1] + scg2[k]) % Mod;
    }
}
void Solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) e[i].clear();
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        e[u].emplace_back(v);
        e[v].emplace_back(u);
    }
    Dfs(1, 0);
    printf("%d\n", f[1]);
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> T;
    while (T--) Solve();
    return 0;
}
/*
游乐园，执行任务？
寝室出门左边走到底那片区域，6人两种颜色衣服，想加入，石头剪刀布，朱和程胜出
我上厕所，穿袜子，出发

model 10-A贴脸射好几发无伤害

🌌 星空知识卡片 06：仙女座星系（M31）

【📍 基础档案】

坐标：仙女座，距地球约 254 万光年，是肉眼能看见的最远天体。

视星等：整团约 3.4 等；不过它表面亮度低，要看清核心那片“雾”，得找暗一点的天。

尺度：直径约 22 万光年，比银河系还大，恒星数以万亿计。

【📖 文科浪漫与神话】

它是仙女座公主安德洛墨达（被珀耳修斯救下的那位）身上的光。
10 世纪波斯天文学家苏菲最早把它记成“小云”。
直到 1923 年，哈勃在 M31 里找到了造父变星——也就是上一张卡片里的那种“标准烛光”
——才证明它在银河系之外：宇宙的尺度在一夜之间被撑大了千万倍。

【🔭 硬核数据与物理】

它正朝我们冲来：以约 110 公里/秒接近，约 45 亿年后将与银河系碰撞并合，融成一个更大的星系。

中心藏着一个约 1 亿倍太阳质量的超大质量黑洞——比银河系中心那位还重。

【🧭 观测指南】

怎么找：先找秋季四边形（飞马座大四边形），从它的左上角沿仙女座 β、μ、ν 这条星链往外延伸，就能看到一小片椭圆形的雾。

城市里只看得到核心亮点；用双筒望远镜看，它像一枚小小的、朦胧的橄榄。
你看它的那一秒，光已经在路上走了 254 万年喵。
*/