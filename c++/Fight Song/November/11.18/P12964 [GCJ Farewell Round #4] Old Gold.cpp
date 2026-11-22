#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1000000007;
const int N = 500005;

int n;
char s[N];
int lastO[N], lastL[N], lastE[N], nextG[N], nextE[N];
ll dp[N], bit[N];
vector<int> expire[N];

void add(int i, ll v) { for (; i <= n; i += i & -i) bit[i] = (bit[i] + v) % MOD; }
ll pref(int i) { ll r = 0; for (; i > 0; i -= i & -i) r += bit[i]; return r % MOD; }
ll rangeSum(int l, int r) { return l > r ? 0 : (pref(r) - pref(l - 1) + MOD) % MOD; }
bool allowed(int i) { return s[i] == '.' || s[i] == 'o'; }
// 第一个使 (j, i) 这对被 j 之后第一个 '>' 破坏的 i
ll expireTime(int j) { int g = nextG[j + 1]; return g > n ? LLONG_MAX : 2LL * g - j; }

int main() {
    int T; scanf("%d", &T);
    for (int tc = 1; tc <= T; tc++) {
        scanf("%s", s + 1); n = strlen(s + 1);
        lastO[0] = lastL[0] = lastE[0] = 0;
        for (int i = 1; i <= n; i++) {
            lastO[i] = s[i] == 'o' ? i : lastO[i - 1];
            lastL[i] = s[i] == '<' ? i : lastL[i - 1];
            lastE[i] = s[i] == '=' ? i : lastE[i - 1];
        }
        nextG[n + 1] = nextE[n + 1] = n + 1;
        for (int i = n; i >= 1; i--) {
            nextG[i] = s[i] == '>' ? i : nextG[i + 1];
            nextE[i] = s[i] == '=' ? i : nextE[i + 1];
        }
        for (int i = 0; i <= n + 1; i++) { bit[i] = 0; dp[i] = 0; expire[i].clear(); }

        for (int i = 1; i <= n; i++) {
            for (int j : expire[i]) add(j, (MOD - dp[j]) % MOD);
            if (!allowed(i)) continue;
            int lo = lastO[i - 1], pl = lastL[i - 1], pe = lastE[i - 1];
            ll val = (lo == 0 && pl == 0 && pe == 0) ? 1 : 0;      // i 是第一个金色
            int L = max({1, lo, 2 * pl - i + 1, pe + 1});           // 中间没有 '=' 的前驱
            val += rangeSum(L, i - 1);
            if (pe) {                                               // pe 处的 '=' 必须是精确中点
                int j = 2 * pe - i;
                if (j >= 1 && allowed(j) && j >= lo && pl < pe && lastE[pe - 1] < j && i < expireTime(j))
                    val += dp[j];
            }
            dp[i] = val % MOD;
            add(i, dp[i]);
            ll u = expireTime(i);
            if (u <= n) expire[u].push_back(i);
        }
        ll ans = 0;
        for (int i = 1; i <= n; i++)                                // i 是最后一个金色
            if (allowed(i) && i >= lastO[n] && nextG[i + 1] > n && nextE[i + 1] > n)
                ans = (ans + dp[i]) % MOD;
        printf("Case #%d: %lld\n", tc, ans);
    }
}
/*
🌌 星空知识卡片 03：天狼星（Sirius）
【📍 基础档案】

坐标：大犬座 α 星，距离地球约 8.6 光年（太阳系最近的邻居之一）。

视星等：−1.46 等（全天夜空最亮的恒星，没有之一）。

光谱型：A1V（蓝白色主序星，表面温度约 9900 K）。

【📖 文科浪漫与神话】
天狼星的名字 Sirius 源自希腊语，意为“灼热的”或“闪耀的”。
在古埃及，它的“偕日升”（每年黎明前第一次升起）标志着尼罗河大洪水的到来，古埃及人甚至以此为基准制定历法。
在中国古代，它属于“二十八宿”中的井宿，被称为“天狼星”，
苏轼在《江城子·密州出猎》中写下“会挽雕弓如满月，西北望，射天狼”，这里的“天狼”指的就是它，
常被古人视为代表战争与侵略的“星宿”。

【🔭 硬核数据与物理】

自带“小弟”：天狼星其实是个双星系统。我们肉眼看到的那颗极亮的叫天狼星 A（主序星），它还有一个伴星叫天狼星 B。
天狼星 B 是一颗白矮星——也就是一颗像太阳这样的恒星死亡后留下的致密残骸，大小和地球差不多，但密度极高。

为什么这么亮？ 它本身确实亮（大约是太阳的25倍），但更重要的是它离我们非常近。
如果把它放到参宿四的位置，它在夜空中就几乎看不见了。

【🧭 观测指南与“闪烁”的秘密】

怎么找：冬季夜空，先找到猎户座的“腰带”，顺着三颗星向左下方（东南方向）画一条线，就会撞上这颗耀眼的蓝白色亮星。
它和猎户座的参宿四、小犬座的南河三，共同组成了著名的“冬季大三角”。

为什么一闪一闪的？ 当你在城市里看低空的天狼星时，会发现它闪烁得非常厉害，甚至能折射出红绿蓝等不同的颜色。
这其实是地球大气层在捣鬼——它的光穿过厚厚的、湍流不断的大气层时发生了折射，并不代表它本身在变颜色。
*/