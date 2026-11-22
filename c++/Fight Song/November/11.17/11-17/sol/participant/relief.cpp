/*
输入：阀门阈值，以及各次询问的初始压力和轮数。
输出：每次独立询问结束时的压力。
功能：线段树求删除位置，按稳定时间分层，用普通计数线段树离线处理。
复杂度：时间 O((n+q) log(n+1))，空间 O(n+q)。
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 100005;
const int MAXQ = 2000005;
const ll INF = 4000000000000000000LL;
int n, q, tot;
ll c[MAXN], t[MAXN], b[MAXN]; // 阈值、删除位置、重复输出
ll mn[MAXN * 4], lazy[MAXN * 4];
ll v[MAXN], h[MAXN]; // 各阶段首层的起点和深度
int w[MAXN], sum[MAXN * 4];
vector<int> src[MAXN], dst[MAXN]; // 各阶段的询问起点、终点事件
int rk[MAXQ], pos[MAXQ];
ll base[MAXQ], ans[MAXQ];

void build(int p, int l, int r){
    if (l == r){
        mn[p] = c[l];
        return;
    }
    int mid = (l + r) / 2;
    build(p * 2, l, mid);
    build(p * 2 + 1, mid + 1, r);
    mn[p] = min(mn[p * 2], mn[p * 2 + 1]);
}

void add(int p, ll val){
    mn[p] += val;
    lazy[p] += val;
}

void push(int p){
    if (lazy[p] == 0) return;
    add(p * 2, lazy[p]);
    add(p * 2 + 1, lazy[p]);
    lazy[p] = 0;
}

// 取最小候选值；平手取最早的阀门，再给它后面的候选值全部加一。
ll popMin(int p, int l, int r){
    if (l == r){
        ll res = mn[p];
        mn[p] = INF;
        return res;
    }
    push(p);
    int mid = (l + r) / 2;
    ll res;
    if (mn[p * 2] <= mn[p * 2 + 1]){
        res = popMin(p * 2, l, mid);
        // 递归路径上的右兄弟，恰好组成选中下标之后的后缀。
        add(p * 2 + 1, 1);
    } else {
        res = popMin(p * 2 + 1, mid + 1, r);
    }
    mn[p] = min(mn[p * 2], mn[p * 2 + 1]);
    return res;
}

void buildCnt(int p, int l, int r){
    sum[p] = r - l + 1;
    if (l == r) return;
    int mid = (l + r) / 2;
    buildCnt(p * 2, l, mid);
    buildCnt(p * 2 + 1, mid + 1, r);
}

void del(int p, int l, int r, int k){
    sum[p]--;
    if (l == r) return;
    int mid = (l + r) / 2;
    if (k <= sum[p * 2]){
        del(p * 2, l, mid, k);
    } else {
        del(p * 2 + 1, mid + 1, r, k - sum[p * 2]);
    }
}

int kth(int p, int l, int r, int k){
    if (l == r) return l;
    int mid = (l + r) / 2;
    if (k <= sum[p * 2]) return kth(p * 2, l, mid, k);
    return kth(p * 2 + 1, mid + 1, r, k - sum[p * 2]);
}

int count(int p, int l, int r, int x){
    if (r <= x) return sum[p];
    int mid = (l + r) / 2;
    if (x <= mid) return count(p * 2, l, mid, x);
    return sum[p * 2] + count(p * 2 + 1, mid + 1, r, x);
}

void init(){
    build(1, 1, n);
    for (int i = 1; i <= n; i++){
        t[i] = popMin(1, 1, n);
        b[i] = t[i] - ll(i);
    }
    ll val = t[1], dep = 1;
    int cnt = 0;
    while (true){
        while (cnt < n && b[cnt + 1] < val) cnt++;
        tot++;
        v[tot] = val;
        h[tot] = dep;
        w[tot] = cnt;
        if (cnt == n) break;
        ll steps = (b[cnt + 1] - val) / ll(cnt) + 1;
        val += steps * ll(cnt);
        dep += steps;
    }
}

void addQ(int id, ll x, ll r){
    if (x <= b[1] || r == 0){
        ans[id] = x;
        return;
    }
    int p = int(upper_bound(v + 1, v + tot + 1, x) - v) - 1;
    ll dep = h[p] + (x - v[p]) / ll(w[p]);
    if (r >= dep){
        ans[id] = b[1];
        return;
    }
    rk[id] = int((x - v[p]) % ll(w[p])) + 1;
    src[p].push_back(id);
    dep -= r;
    p = int(upper_bound(h + 1, h + tot + 1, dep) - h) - 1;
    base[id] = v[p] + (dep - h[p]) * ll(w[p]);
    dst[p].push_back(id);
}

void solve(){
    buildCnt(1, 1, n);
    int last = n;
    for (int i = tot; i >= 1; i--){
        assert(sum[1] == w[i]);
        // 同一阶段先求出源区间在参考层中的左端点，再回答目标事件。
        for (int id: src[i]) pos[id] = kth(1, 1, n, rk[id]);
        for (int id: dst[i]){
            ans[id] = base[id] + ll(count(1, 1, n, pos[id])) - 1;
        }
        if (i == 1) break;
        // 合并回前一个阶段。同层从右向左处理，左侧排名保持不变。
        while (last > 0 && b[last] >= v[i - 1]){
            // t[last] 与它左侧的压力具有同一个父亲，删除两者间的边界。
            int k = int(t[last] - v[i]) + 1;
            del(1, 1, n, k);
            last--;
        }
    }
}

// 批量读写，处理最多两百万组询问的文件。
const int BS = 1 << 16;
char ib[BS], ob[BS];
int ip, il, op;
int gc(){
    if (ip == il){
        il = int(fread(ib, 1, BS, stdin));
        ip = 0;
        if (il == 0) return EOF;
    }
    return ib[ip++];
}
ll read(){
    int ch = gc();
    while (ch != EOF && ch <= ' ') ch = gc();
    ll x = 0;
    while ('0' <= ch && ch <= '9'){
        x = x * 10 + ch - '0';
        ch = gc();
    }
    return x;
}
void flush(){
    fwrite(ob, 1, op, stdout);
    op = 0;
}
void pc(char ch){
    if (op == BS) flush();
    ob[op++] = ch;
}
void write(ll x){
    char s[20];
    int k = 0;
    do {
        s[k++] = char('0' + x % 10);
        x /= 10;
    } while (x > 0);
    while (k > 0) pc(s[--k]);
    pc('\n');
}

int main(){
    freopen("relief.in", "rb", stdin);
    freopen("relief.out", "wb", stdout);
    n = int(read());
    q = int(read());
    for (int i = 1; i <= n; i++) c[i] = read();
    init();
    for (int i = 1; i <= q; i++){
        ll x = read();
        ll r = read();
        addQ(i, x, r);
    }
    solve();
    for (int i = 1; i <= q; i++) write(ans[i]);
    flush();
    return 0;
}
