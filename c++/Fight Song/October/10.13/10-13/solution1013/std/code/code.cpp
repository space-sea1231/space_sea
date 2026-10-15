#include <bits/stdc++.h>
using namespace std;

namespace z {

#define int long long
const int N = 5e5 + 5, mod = 1234567;
vector<int> p[N];
int n, m, cnt, f[N], rt[N], ch[N][11], tag[N];
vector<string> v[N];
void add(int &x, int y) {
    x += y;
    if(x >= mod) x -= mod;
}
void ins(int p, string s) {
    for(auto c : s) {
        if(!ch[p][c - '0']) ch[p][c - '0'] = ++cnt, tag[cnt] = 1;
        p = ch[p][c - '0'];
    }
    f[p] = mod - 1; // -1
}
void app(int u, int x) {
    f[u] = f[u] * x % mod;
    tag[u] = tag[u] * x % mod;
}
void pd(int u) {
    for(int i = 0; i < 10; i++) 
        if(ch[u][i]) app(ch[u][i], tag[u]);
    tag[u] = 1;
}
int merge1(int x, int y, int sx, int sy) {
    if(x > y) swap(x, y), swap(sx, sy);
    if(!y) return 0;
    if(!x) {
        app(y, sx);
        return y;
    }
    int sum = mod - sx * sy % mod;
    pd(x); pd(y);
    add(sx, f[x]); add(sy, f[y]); 
    add(sum, sx * sy % mod);
    for(int i = 0; i < 10; i++) ch[x][i] = merge1(ch[x][i], ch[y][i], sx, sy);
    f[x] = sum;
    return x;
}
int merge2(int x, int y) {
    if(!x || !y) return x + y;
    pd(x); pd(y);
    for(int i = 0; i < 10; i++) ch[x][i] = merge2(ch[x][i], ch[y][i]);
    add(f[x], f[y]);
    return x;
}
void dfs(int u) {
    for(auto v : p[u]) dfs(v);
    f[rt[u] = ++cnt] = 1; tag[cnt] = 1;
    for(auto s : v[u]) ins(rt[u], s);
    for(auto v : p[u]) rt[u] = merge1(rt[u], rt[v], 0, 0);
    int tmp = 0;
    for(int i = 0; i < 10; i++) tmp = merge2(tmp, ch[rt[u]][i]);
    if(!tmp) tag[tmp = ++cnt] = 1;
    f[tmp] = (f[rt[u]] * 10 + f[tmp]) % mod;
    rt[u] = tmp;
}
void main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);
    for(int i = 0; i < N; i++) tag[i] = 1;
    cin >> n >> m;
    for(int i = 2; i <= n; i++) {
        int x; cin >> x;
        p[++x].push_back(i);
    }
    for(int i = 1, x; i <= m; i++) {
        string s; cin >> x >> s;
        v[++x].push_back(s);
    }
    dfs(1);
    int ans = 1;
    for(int i = 1; i <= n; i++) ans = ans * 10 % mod;
    cout << (ans - f[rt[1]] + mod) % mod << '\n';

}

#undef int

}


int main()
{
	freopen("code.in", "r", stdin);
	freopen("code.out", "w", stdout);
    z::main();
    return 0;
}

