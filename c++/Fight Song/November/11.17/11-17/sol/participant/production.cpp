/*
输入：n 个站的容量、相邻边收益，以及 q 个独立区间。
输出：每个区间的最大收益。
功能：边际 DP、分层匹配与递归分治，不展开能源单位。
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 200000 + 5;
int n, q, a[MAXN], w[MAXN];
ll ans[MAXN];
struct qry{
    int l, r;
} ask[MAXN];
vector<int> qs[MAXN];

struct blk{
    ll val;
    int len;
};
// 末端边际非增；段的实际值为 sgn * val + tag。
struct slope{
    deque<blk> que;
    bool rev;
    int sz;
    ll sgn, tag, sum;
    blk &back(){
        return rev ? que.front() : que.back();
    }
    void add(ll val, int len){
        if (len == 0) return;
        val = (val - tag) * sgn;
        sz += len;
        sum += val * len;
        if (!que.empty() && back().val == val){
            back().len += len;
        } else if (rev){
            que.push_front(blk{val, len});
        } else {
            que.push_back(blk{val, len});
        }
    }
    void erase(int len){
        while (len > 0){
            blk &x = back();
            int take = min(len, x.len);
            sum -= x.val * take;
            sz -= take;
            len -= take;
            x.len -= take;
            if (x.len == 0){
                if (rev){
                    que.pop_front();
                } else {
                    que.pop_back();
                }
            }
        }
    }
    void reset(int cap){
        que.clear();
        rev = false;
        sz = 0;
        sgn = 1;
        tag = 0;
        sum = 0;
        add(0, cap);
    }
    ll trans(int wt, int cap){
        rev = !rev;
        sgn = -sgn;
        tag = wt - tag;
        if (sz > cap) erase(sz - cap);
        while (!que.empty() && sgn * back().val + tag <= 0) erase(back().len);
        add(0, cap - sz);
        return sgn * sum + tag * sz;
    }
} dp;

struct seg{
    int r;
    ll val, pre;
};
// 最终损失的等值段；第 0 段是空前缀哨兵。
struct line{
    vector<seg> a{{0, 0, 0}};
    void add(int len, ll val){
        if (len == 0) return;
        int r = a.back().r + len;
        ll sum = a.back().pre + ll(len) * val;
        if (a.back().r > 0 && a.back().val == val) a.pop_back();
        a.push_back({r, val, sum});
    }
    int find(int pos) const{
        int l = 1, r = int(a.size()) - 1;
        while (l < r){
            int mid = (l + r) / 2;
            if (a[mid].r >= pos){
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        return l;
    }
    ll at(int pos) const{
        return a[find(pos)].val;
    }
    ll pre(int pos) const{
        if (pos == 0) return 0;
        int p = find(pos);
        return a[p - 1].pre + ll(pos - a[p - 1].r) * a[p].val;
    }
};
struct state{
    int l, r;
    ll val, opt; // [l,r] 覆盖成 val；opt 是完整容量最优值。
} ver[MAXN];

line build(int u, int v, int dir){
    int cap = a[u], len = abs(v - u) + 1, l = 1, r = cap;
    ll low = 0, high = cap, f0 = 0, f1 = 0, g0 = 0, g1 = 0, val = 0, opt = 0;
    line res;
    vector<blk> right;
    dp.reset(cap);
    ver[u] = state{1, cap, 0, 0};
    for (int i = 2; i <= len; i++){
        int pos = u + (i - 1) * dir, e = min(pos, pos - dir);
        opt += dp.trans(w[e], a[pos]);
        // 同一贯通层：保留近端的答案 f，去掉近端的答案 g。
        ll f = max(f1, f0 + w[e]);
        ll g = i == 2 ? 0 : max(g1, g0 + w[e]);
        f0 = f1;
        f1 = f;
        g0 = g1;
        g1 = g;
        if (i % 2 == 0){
            high = low + a[pos];
        } else {
            low = high - a[pos];
        }
        if (l <= r){
            // [l,r] 是贯通高度反向后的损失下标；先固定退出部分的旧值。
            ll ql = max(ll(l), ll(cap) - high + 1);
            ll qr = min(ll(r), ll(cap) - low);
            if (ql > qr){
                res.add(r - l + 1, val);
                l = 1;
                r = 0;
            } else {
                res.add(int(ql) - l, val);
                if (qr < r) right.push_back(blk{val, r - int(qr)});
                l = int(ql);
                r = int(qr);
            }
        }
        val = f1 - g1;
        ver[pos] = state{l, r, val, opt};
    }
    res.add(r - l + 1, val);
    reverse(right.begin(), right.end());
    for (blk x: right) res.add(x.len, x.val);
    return res;
}

ll get(const line &d, const state &x, int pos){
    if (x.l <= pos && pos <= x.r) return x.val;
    return d.at(pos);
}
// 从最终数组中扣去覆盖部分，再补上历史常数段。
ll pre(const line &d, const state &x, int pos){
    ll res = d.pre(pos);
    int l = max(1, x.l);
    int r = min(pos, x.r);
    if (l <= r){
        res += ll(r - l + 1) * x.val - d.pre(r) + d.pre(l - 1);
    }
    return res;
}
ll calc(int ql, int qr, int mid, const line &left, const line &right){
    const state &x = ver[ql], &y = ver[qr];
    int l = 0, r = min(a[mid], a[mid + 1]);
    if (get(left, x, r) + get(right, y, r) <= w[mid]){
        l = r;
    } else if (get(left, x, 1) + get(right, y, 1) > w[mid]){
        r = 0;
    }
    // 损失非降，二分最后一次净收益非负的操作。
    while (l < r){
        int pos = (l + r + 1) / 2;
        if (get(left, x, pos) + get(right, y, pos) <= w[mid]){
            l = pos;
        } else {
            r = pos - 1;
        }
    }
    return x.opt + y.opt + ll(l) * w[mid] - pre(left, x, l) - pre(right, y, l);
}
// 每个分治结点的中点唯一，询问预先挂桶等价于逐层分流。
void dfs(int l, int r){
    if (l == r) return;
    int mid = (l + r) / 2;
    if (!qs[mid].empty()){
        line x = build(mid, l, -1), y = build(mid + 1, r, 1);
        for (int id: qs[mid]) ans[id] = calc(ask[id].l, ask[id].r, mid, x, y);
    }
    // 本层两份分段表已经释放，历史摘要可由子结点覆盖。
    dfs(l, mid);
    dfs(mid + 1, r);
}
void init(){
    for (int i = 1; i <= q; i++){
        int l = 1, r = n;
        while (l < r){
            int mid = (l + r) / 2;
            if (ask[i].l <= mid && ask[i].r > mid){
                qs[mid].push_back(i);
                break;
            }
            if (ask[i].r <= mid){
                r = mid;
            } else {
                l = mid + 1;
            }
        }
    }
}
int main(){
    freopen("production.in", "r", stdin);
    freopen("production.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n - 1; i++) cin >> w[i];
    for (int i = 1; i <= q; i++) cin >> ask[i].l >> ask[i].r;
    init();
    dfs(1, n);
    for (int i = 1; i <= q; i++) cout << ans[i] << '\n';
    return 0;
}