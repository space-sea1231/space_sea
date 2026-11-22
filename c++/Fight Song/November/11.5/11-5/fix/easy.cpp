#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e6 + 10;
const int M = 1e7 + 10;
const int Mod = 998244353;

int n, m;
int cnt;
int a[N];
int pre[M], ans[N];
int prime[N];
bool vis[M];

void Prime() {
    for (int i = 2; i < M; i++) {
        if (!vis[i]) prime[++cnt] = i;
        for (int j = 1; j <= cnt && i * prime[j] < M; j++) {
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0) continue;
        }
    }
}
struct Query_ {
    int l, r;
    int id;

    bool operator<(const Query_ &s) const { return r < s.r; }
}; Query_ q[N];

namespace SegmentTree {
    struct Node {
        int val, vis;
    }; Node node[N << 2];

    void Build(int p, int l, int r) {
        // cerr << "Build: " << p << " " << l << " " << r << "\n";
        node[p].vis = 1;
        if (l == r) {
            node[p].val = 1;
            return ;
        }
        int mid = l + r >> 1;
        Build(p << 1, l, mid);
        Build(p << 1 | 1, mid + 1, r);
    }
    void Update(int p, int l, int r, int L, int R, int val) {
        // cerr << "Update: " << p << " " << l << " " << r << " " << L << " " << R << " " << val << "\n";
        if (L <= l && r <= R) {
            node[p].val = (ll)node[p].val * val % Mod;
            node[p].vis = (ll)node[p].vis * val % Mod;
            return ;
        }
        int mid = l + r >> 1;
        if (L <= mid) Update(p << 1, l, mid, L, R, val);
        if (mid < R) Update(p << 1 | 1, mid + 1, r, L, R, val);
    }
    int Query(int p, int l, int r, int pos) {
        // cerr << "Query: " << p << " " << l << " " << r << " " << pos << "\n";
        if (l == r) return node[p].val;
        int mid = l + r >> 1;
        if (pos <= mid) return (ll)node[p].vis * Query(p << 1, l, mid, pos) % Mod;
        if (mid < pos) return (ll)node[p].vis * Query(p << 1 | 1, mid + 1, r, pos) % Mod;
    }
} using namespace SegmentTree;

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    Prime();
    cin >> n;
    Build(1, 1, n);
    for (int i = 1; i <= n; i++) cin >> a[i];
    cin >> m;
    for (int i = 1; i <= m; i++) {
        cin >> q[i].l >> q[i].r;
        q[i].id = i;
    }
    sort(q + 1, q + m + 1);
    for (int i = 1; i <= m; i++) {
        // cerr << q[i].l << " " << q[i].r << "\n";
        for (int j = q[i - 1].r + 1; j <= q[i].r; j++) {
            for (int k = 1; k <= cnt && prime[k] * prime[k] <= a[j]; k++) {
                if (a[j] % prime[k] == 0) {
                    a[j] /= prime[k];
                    // printf("Debug %d: has prime %d\n", j, prime[k]);
                    // cerr << "Debug1:" << pre[prime[k]] + 1 << " " << j << " " << prime[k] << "\n";
                    Update(1, 1, n, pre[prime[k]] + 1, j, prime[k]);
                    while (a[j] % prime[k] == 0) a[j] /= prime[k]; 
                    pre[prime[k]] = j;
                }
            }
            if (a[j] > 1) {
                // cerr << "Debug1:" << pre[a[j]] + 1 << " " << j << " " << a[j] << "\n";
                // printf("Debug %d: has prime %d\n", j, a[j]);
                Update(1, 1, n, pre[a[j]] + 1, j, a[j]);
                pre[a[j]] = j;
            }
        }
        ans[q[i].id] = Query(1, 1, n, q[i].l);
    }
    for (int i = 1; i <= m; i++) printf("%d\n", ans[i]);
    return 0;
}
/*
这个世界 是什么模样
走过山水一程 梦一场
那迎风呐喊的海浪
要多久 多久才会遇上
冒险的人 是否会感伤
终其璀璨一生 谁收藏
那深埋心底的愿望
要多久 多久才会登场
沿途一身泥泞 跌撞的是我
忍痛缓行不回头的 也是我
就让一路曲折 每一道伤口
洗净我的脆弱
原来 咽回去的泪
才能 淹没了脆弱
你 发誓更勇敢 一生与梦相拥
还 想要继续吗
要 逆风不退啊
让璀璨住进 你眼眸
别怕 未来的模样
辜负 曾经的凝望
有 多少理想 就有 多少次传唱
那 沿途的风浪
也 不过就这样
这一路光景 有你在身旁
Rap：
他们说要越过 前方风沙 必须低着头
他们说要绕过 蜿蜒的河 才能往前走
他们说烫要放手 太远要换个路口
如果得不到谁的认同 那就不算拥有
没人能够决定 谁的一生 应该怎么活
没人能够定义 谁的天空 是什么颜色
没人未梦就先懂 只是单纯相信着
背向光的英雄 每张轮廓
出自平凡的沉默
沿途一身泥泞 跌撞的是我
忍痛缓行不回头的 也是我
就让一路曲折 每一道伤口
洗净我的脆弱
原来 咽回去的泪
才能 淹没了脆弱
你 发誓更勇敢 一生与梦相拥
还 想要继续吗
要 逆风不退啊
让痛苦住进 你眼眸
别怕 未来的模样
辜负 曾经的凝望
有 多少理想 就有 多少次传唱
那 沿途的风浪
也 不过就这样
这一路光景 有你在身旁
要炙热啊 要不忘啊 要勇往啊
起风了 呼唤了 你还在等什么
挥手了 再见了 别不舍回头啊
向心中的梦啊 去追吧
要能留下伤痕才算活过
愿你记得
愿你哭过 不惧脆弱
*/