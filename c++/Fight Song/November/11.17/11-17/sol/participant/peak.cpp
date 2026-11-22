/*
输入：原序列 a、单位费用 c、m 个区间最大值要求。
输出：最小费用，无解时输出 -1。
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAXN = 200005, LIM = 1000000001;
const ll INF = 4000000000000000000LL;
struct req{
    int l, r, v;
} aReq[MAXN];
int n, m, a[MAXN], c[MAXN], val[MAXN], sz;
vector<int> add[MAXN], pos[MAXN], fix[MAXN];
vector<ll> cost[MAXN];
vector<pii> seg[MAXN];

ll f[MAXN];
int need[MAXN];

int gid(int x){
    return int(lower_bound(val + 1, val + sz + 1, x) - val);
}

bool init(){
    sort(val + 1, val + m + 1);
    sz = int(unique(val + 1, val + m + 1) - (val + 1));
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    for (int i = 1; i <= n; i++){
        for (int j: add[i]) pq.push({aReq[j].v, aReq[j].r});
        while (!pq.empty() && pq.top().second < i) pq.pop();
        int up = pq.empty() ? LIM : pq.top().first;
        if (a[i] > up) return false;
        if (up == LIM) continue;
        int id = gid(up);
        if (a[i] == up){
            fix[id].push_back(i); // 在当前
        } else {
            pos[id].push_back(i);
            cost[id].push_back(ll(c[i]) * (up - a[i]));
        }
    }
    for (int i = 1; i <= m; i++){
        int l = aReq[i].l, r = aReq[i].r, id = gid(aReq[i].v);
        const vector<int> &p = pos[id], &s = fix[id];
        auto it = lower_bound(s.begin(), s.end(), l);
        if (it != s.end() && *it <= r) continue;
        int x = int(lower_bound(p.begin(), p.end(), l) - p.begin()) + 1;
        int y = int(upper_bound(p.begin(), p.end(), r) - p.begin());
        if (x > y) return false;
        seg[id].push_back({x, y});
    }
    return true;
}

ll solve(int id){
    if (seg[id].empty()) return 0;
    int k = int(pos[id].size()), last = 0, l = 0;
    fill(need + 1, need + k + 1, 0);
    for (pii s: seg[id]){
        need[s.second] = max(need[s.second], s.first);//右端点的最大左端点
        last = max(last, s.first); // last是所有需要的中最大左端点
        //seg里是所有需要匹配的区间
    }
    deque<int> dq{0};
    // 右端点小于 i 的区间，要求上一个选点的下标至少为 l。
    for (int i = 1; i <= k; i++){
        l = max(l, need[i - 1]);
        while (!dq.empty() && dq.front() < l) dq.pop_front();
        f[i] = INF;
        if (dq.empty()) continue;
        f[i] = f[dq.front()] + cost[id][i - 1];
        while (!dq.empty() && f[dq.back()] >= f[i]) dq.pop_back();
        dq.push_back(i);
    }
    return *min_element(f + last, f + k + 1);
}

int main(){
    // freopen("peak.in", "r", stdin);
    // freopen("peak.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> c[i];
    for (int i = 1; i <= m; i++){
        req &s = aReq[i];
        cin >> s.l >> s.r >> s.v;
        val[i] = s.v;
        add[s.l].push_back(i);
    }
    if (!init()){
        cout << -1 << '\n';
        return 0;
    }
    ll ans = 0;
    for (int i = 1; i <= sz; i++){
        ll res = solve(i);
        if (res == INF){
            cout << -1 << '\n';
            return 0;
        }
        ans += res;
    }
    cout << ans << '\n';
    return 0;
}
