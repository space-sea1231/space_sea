#include <bits/stdc++.h>

#define ll long long
#define x first
#define y second
#define int ll
typedef unsigned long long ull;
typedef std::pair<int,int> pii;

using namespace std;

const int maxn=5e6+10;
const int mo=1e9+7;
const ll inf = 2e18;

inline int read(){
    int ret=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
    while(isdigit(ch)){ret=ret*10+ch-'0';ch=getchar();}
    return ret*f;
}

int a[maxn];
int b[maxn];
int P[maxn];    
int D[maxn];    
int temp_b[maxn]; 
int n, q;

struct Node {
    ll min_b;    
    ll min_even;  
    ll max_odd;  
    ll lazy_b;
    ll lazy_even;
    ll lazy_odd;
} tree[maxn << 2];

#define lc (p << 1)
#define rc (p << 1 | 1)

inline void pushup(int p) {
    tree[p].min_b = min(tree[lc].min_b, tree[rc].min_b);
    tree[p].min_even = min(tree[lc].min_even, tree[rc].min_even);
    tree[p].max_odd = max(tree[lc].max_odd, tree[rc].max_odd);
}

inline void apply_b(int p, ll val) {
    tree[p].min_b += val;
    tree[p].lazy_b += val;
}

inline void apply_even(int p, ll val) {
    if (tree[p].min_even != inf) tree[p].min_even += val; 
    tree[p].lazy_even += val;
}

inline void apply_odd(int p, ll val) {
    if (tree[p].max_odd != -inf) tree[p].max_odd += val;
    tree[p].lazy_odd += val;
}

inline void pushdown(int p) {
    if (tree[p].lazy_b) {
        apply_b(lc, tree[p].lazy_b);
        apply_b(rc, tree[p].lazy_b);
        tree[p].lazy_b = 0;
    }
    if (tree[p].lazy_even) {
        apply_even(lc, tree[p].lazy_even);
        apply_even(rc, tree[p].lazy_even);
        tree[p].lazy_even = 0;
    }
    if (tree[p].lazy_odd) {
        apply_odd(lc, tree[p].lazy_odd);
        apply_odd(rc, tree[p].lazy_odd);
        tree[p].lazy_odd = 0;
    }
}

void build(int p, int l, int r) {
    tree[p].lazy_b = tree[p].lazy_even = tree[p].lazy_odd = 0;
    if (l == r) {
        tree[p].min_b = b[l];
        tree[p].min_even = (l % 2 == 0) ? P[l] : inf;  // 奇数节点不参与 min_even
        tree[p].max_odd = (l % 2 != 0) ? P[l] : -inf; // 偶数节点不参与 max_odd
        return;
    }
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    pushup(p);
}

void update_b(int p, int l, int r, int ql, int qr, ll val) {
    if (ql > qr) return;
    if (ql <= l && r <= qr) { apply_b(p, val); return; }
    pushdown(p);
    int mid = (l + r) >> 1;
    if (ql <= mid) update_b(lc, l, mid, ql, qr, val);
    if (qr > mid) update_b(rc, mid + 1, r, ql, qr, val);
    pushup(p);
}

void update_even(int p, int l, int r, int ql, int qr, ll val) {
    if (ql > qr) return;
    if (ql <= l && r <= qr) { apply_even(p, val); return; }
    pushdown(p);
    int mid = (l + r) >> 1;
    if (ql <= mid) update_even(lc, l, mid, ql, qr, val);
    if (qr > mid) update_even(rc, mid + 1, r, ql, qr, val);
    pushup(p);
}

void update_odd(int p, int l, int r, int ql, int qr, ll val) {
    if (ql > qr) return;
    if (ql <= l && r <= qr) { apply_odd(p, val); return; }
    pushdown(p);
    int mid = (l + r) >> 1;
    if (ql <= mid) update_odd(lc, l, mid, ql, qr, val);
    if (qr > mid) update_odd(rc, mid + 1, r, ql, qr, val);
    pushup(p);
}

inline void solve(){
    n = read(); q = read();
    for(int i=0; i<=n; i++){
        a[i] = read();
        b[i] = a[i] - 2;
        if(i == 0 || i == n) b[i]++;
        
        D[i] = (i == 0) ? b[i] : (b[i] - b[i-1]);
        
        ll A_val = (i % 2 == 0) ? b[i] : -b[i];
        P[i] = (i == 0) ? A_val : P[i-1] + A_val;
    }
    D[n+1] = 0;
    build(1, 0, n);

    for(int query = 1; query <= q; query++){
        int L = read(), R = read();
        ll delta = read();
        int opt = read();

        D[L] += delta;
        D[R+1] -= delta;

        update_b(1, 0, n, L, R, delta);

        ll v = (L % 2 == 0) ? delta : -delta;
        if (L % 2 == 0) {
            update_even(1, 0, n, L, n, v);
            if (R % 2 == 0) update_odd(1, 0, n, R + 1, n, v);
            else update_even(1, 0, n, R + 1, n, -v);
        } else {
            update_odd(1, 0, n, L, n, v);
            if (R % 2 != 0) update_even(1, 0, n, R + 1, n, v);
            else update_odd(1, 0, n, R + 1, n, -v);
        }

        bool valid = true;
        if (tree[1].min_b < 0) valid = false; 
        if (tree[1].max_odd > tree[1].min_even) valid = false;
        if (tree[1].min_even < 0) valid = false;

        if (!valid) {
            puts("No");
        } else {
            puts("Yes");
            if (opt == 1) {
                ll mx = tree[1].min_even;
                ll cur_b = 0;

                for(int i=0; i<=n; i++){
                    cur_b += D[i];
                    temp_b[i] = cur_b;
                }
                
                for(int i=1; i<=mx; i++) putchar('L');
                temp_b[0] -= mx;
                for(int i=1; i<=n; i++){
                    putchar('R');
                    ll step = min(temp_b[i-1], temp_b[i]);
                    temp_b[i] -= step;
                    temp_b[i-1] -= step;
                    for(ll j=1; j<=step; j++) {
                        putchar('L');
                        putchar('R');
                    }
                }
                for(ll j=1; j<=temp_b[n]; j++) putchar('R');
                for(int i=1; i<=n; i++) putchar('L');
                putchar('\n');
            }
        }
    }
}

signed main(){    
//	freopen("data/2.in","r",stdin);
//	freopen("data/2.out","w",stdout);
    int t=read();
    for(int i=1;i<=t;i++) solve();
    return 0;
}
