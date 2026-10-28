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
const int N = 2e5 + 10;
const int K = 20;

int n, X, Y;
int ans;
int f[N][K];
int depb[N], depa[N];
bool vis[N];
vector<int> e1[N], e2[N];
pair<int, int> edge[N];

void Dfs1(int u, int fa) { // A剑旗 B凯撒
    depb[u] = depb[fa] + 1;
    for (int v : e2[u]) {
        if (v == fa) continue;
        f[v][0] = u;
        for (int i = 1; i < K; i++) f[v][i] = f[f[v][i - 1]][i - 1];
        Dfs1(v, u);
    }
}
void Dfs2(int u, int fa) {
    depa[u] = depa[fa] + 1;
    if (depa[u] >= depb[u]) return ;
    if (vis[u]) { printf("forever\n"), exit(0); }
    ans = max(ans, depb[u]);
    for (int v : e1[u]) {
        if (v == fa) continue;
        Dfs2(v, u);
    }
}
int Dist(int x, int y) {
    if (depb[x] < depb[y]) swap(x, y);
    int dis = 0;
    for (int i = K - 1; ~i; i--) {
        if (depb[f[x][i]] >= depb[y]) {
            x = f[x][i];
            dis += (1 << i);
        }
    }
    if (x == y) return dis;
    for (int i = K - 1; ~i; i--) {
        if (f[x][i] ^ f[y][i]) {
            x = f[x][i];
            y = f[y][i];
            dis += (1 << i + 1);
        }
    }
    return dis + 2;
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> X >> Y;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        e1[u].emplace_back(v);
        e1[v].emplace_back(u);
        edge[i] = make_pair(u, v);
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        e2[u].emplace_back(v);
        e2[v].emplace_back(u);
    }
    depa[0] = depb[0] = -1;
    Dfs1(Y, 0);
    for (int i = 1; i < n; i++) {
        int u = edge[i].first, v = edge[i].second;
        if (Dist(u, v) >= 3) vis[u] = vis[v] = true;
    }
    Dfs2(X, 0);
    printf("%d\n", ans << 1);
    return 0;
}
/*
梦境或许会迟到，但永远不会缺席喵！
梦境开始了
喵
阳光穿透云层，为这片接近黄昏的城市染上了一层光辉
结束了一天的学习，本喵舒服的伸了懒腰，“下课了喵！可以钻进舒服的被窝了awa”
“啪！”，机房的大门突然被人一脚踹开
“所有人不许动！这层楼已经被我们控制了！“
说话的是隔壁机房的大高加索牧羊犬，我们对此有些意外但丝毫不慌
3 hours later...
“好无聊啊喵“，本喵百无聊赖的趴在了键盘上，看着被空格逐渐填满的代码行
“一起跑出去玩吗？”说话的是旁边的周周犬。“好啊喵！”本喵一个激灵，跟着周周犬开始了“阳光下的盛大逃亡”
我们以迅雷不及掩耳盗铃儿响叮当仁不让之势冲出了机房，直直着跳进了楼梯间，旁边的大高加索牧羊犬甚至都没反应过来，我们便已冲下了一层
隐约间，我好像看到我们前面还有一个模糊的身影，长长的一条，怎么这么像隔壁机房的刘狗子？
诶？怎么周周犬越跑越快了？不对，我怎么下降速度变得这么慢了？像是漂浮在太空中一样
身后的大高越追越近，我赶忙使出吃猫奶的力气往下跑去，终于在被抓住的前一喵冲出了一楼
“呼，逃出来了喵(〃'▽'〃)”我高兴的看向旁边的周周犬，却看到了一只黑洞洞的枪管，直挺挺的顶在喵脑门上
“发现一名人质”举着枪的那个人拿起一个对讲机，我看到他身后还有源源不断的人涌了进来。不知道什么时候科技馆一楼已经变成了战地1中流血盛宴中的C点
“是闹着玩的吗？”为首那人问我
“是的喵”我立马干脆利落的回答（我也不知道怎么就这么笃定喵╮(╯▽╰)╭）
“哦，那没事了”一瞬间，一厅的人撤的干干净净
喵
然后喵...就醒了
梦境结束了喵
*/