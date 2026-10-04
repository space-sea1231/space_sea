#include <iostream>
#include <cstdio>
using namespace std;
typedef long long ll;

const int N = 1e6 + 10;
const int Mod = 1e9;

int t, n, m;
int f[N], w[N];
ll c[N];
ll val[N];
bool vis[N];

int Find(int x) {
    if (f[x] == x) return x;
    int fa = Find(f[x]);
    c[x] = (ll)w[x] * c[f[x]] + c[x];
    w[x] *= w[f[x]];
    return f[x] = fa;
}

bool Caged(int a, int b, ll d) {
    int fa = Find(a), fb = Find(b);
    if (fa != fb) {
        int new_w = -w[a] * w[b];
        ll new_c = (d - c[a] - c[b]) * w[b];
        
        if (vis[fa] && vis[fb]) {
            if (val[fb] != (ll)new_w * val[fa] + new_c) return false;
        }
        
        f[fb] = fa;
        w[fb] = new_w;
        c[fb] = new_c;
        
        if (vis[fb] && !vis[fa]) {
            vis[fa] = true;
            val[fa] = (val[fb] - new_c) * new_w;
        }
        return true;
    } else {
        ll sumW = w[a] + w[b];
        ll sumC = c[a] + c[b];
        if (sumW == 0) return sumC == d;
        if ((d - sumC) % sumW != 0) return false;
        ll V = (d - sumC) / sumW;
        if (vis[fa]) {
            if (val[fa] != V) return false;
        } else {
            vis[fa] = true;
            val[fa] = V;
        }
        return true;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> t;
    while (t--) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) {
            f[i] = i; w[i] = 1;
            c[i] = val[i] = 0;
            vis[i] = false;
        }
        int k = 0;
        for (int i = 1; i <= m; i++) {
            ll a, b, d;
            cin >> a >> b >> d;
            a = (a + k - 1) % n + 1;
            b = (b + k - 1) % n + 1;
            d = (d + k) % Mod + 1;
            if (Caged((int)a, (int)b, d * 2)) {
                cout << "Yes\n";
                k++;
            } else {
                cout << "No\n";
            }
        }
    }
    return 0;
}