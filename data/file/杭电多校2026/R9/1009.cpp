#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define vt(tp) vector<tp>
#define arr(x) array<ll,x>
#define arri(x) array<int,x>
#define ls (idx<<1)
#define rs (idx<<1|1)
#define all(x) x.begin(),x.end()
const ll Mod = 998244353;

ll M(ll x){
    x %= Mod;
    return x + (x >> 63 & Mod);
}

template <typename T>
void add(T &x,T y){
    x = M(x + y);
}

template <typename T>
void mul(T &x,T y){
    x = M(1ll * x * y);
}

ll ex_gcd(ll a,ll b,ll &x,ll &y){
    if(b == 0){
        x = 1;
        y = 0;
        return a;
    }
    ll d;
    d = ex_gcd(b,a % b,y,x);
    y = y - a / b * x;
    return d;
}

int Inverse(ll q){
    ll x,y;
    ex_gcd(M(q),Mod,x,y);
    return M(x);
}

ll qp(ll x,ll y){
    if(y < 0)return qp(Inverse(x),-y);
    ll res = 1,unit = x;
    while(y){
        if(y & 1)mul(res,unit);
        mul(unit,unit);
        y >>= 1;
    }
    return res;
}

struct DSU{
    vt(int) pre,sum,h;
    void init(int n){
        pre.resize(n);
        sum.resize(n);
        h.resize(n);
        iota(all(pre),0);
    }
    int find(int x){
        if(pre[x] == x)return x;
        return find(pre[x]);
    }
    int merge(int x,int y,vt(arri(3)) &stk){
        int fx = find(x),fy = find(y);
        if(h[fx] < h[fy])swap(fx,fy);
        stk.push_back({0,fy,pre[fy]});
        pre[fy] = fx;
        stk.push_back({1,fx,sum[fx]});
        add(sum[fx],sum[fy]);
        stk.push_back({2,fx,h[fx]});
        h[fx] += h[fx] == h[fy];
        return fx;
    }
};

void solve(){
    int n,m,q;
    cin >> n >> m >> q;
    int N = (n - 1) * (m - 1) + 1,N2 = N << 1;
    int tot = N2,val = 0;
    auto id = [&](int x,int y) -> int {
        if(x < 0 || y < 0 || x >= n - 1 || y >= m - 1)return 0;
        return x * (m - 1) + y + 1;
    };
    vt(vt(arri(2))) vert(n-1,vt(arri(2))(m)),hori(n,vt(arri(2))(m-1));
    vt(vt(int)) lstv0(n-1,vt(int)(m)),lsth0(n,vt(int)(m-1));
    vt(vt(int)) lstv1(n-1,vt(int)(m)),lsth1(n,vt(int)(m-1));
    vt(vt(arri(5))) info((q+1)<<2);  // op,tp,x,y,w
    vt(arri(3)) stk;                 // op,u,w 
    DSU dsu;
    dsu.init(N2);

    for(int i = 0;i < n - 1;++i){
        for(int j = 0;j < m;++j){
            ll t;
            cin >> t;
            t = M(t);
            vert[i][j][0] = t;
        }
    }
    for(int i = 0;i < n;++i){
        for(int j = 0;j < m - 1;++j){
            ll t;
            cin >> t;
            t = M(t);
            hori[i][j][0] = t;
        }
    }
    for(int i = 0;i < n - 1;++i){
        for(int j = 0;j < m;++j){
            int t;
            cin >> t;
            vert[i][j][1] = t;
        }
    }
    for(int i = 0;i < n;++i){
        for(int j = 0;j < m - 1;++j){
            int t;
            cin >> t;
            hori[i][j][1] = t;
        }
    }

    auto upd = [&](auto &&self,int l0,int r0,arri(5) val,int l,int r,int idx) -> void {
        if(l > r0 || r < l0)return;
        if(l >= l0 && r <= r0){
            info[idx].push_back(val);
            return;
        }
        int mid = (l + r) >> 1;
        self(self,l0,r0,val,l,mid,ls);
        self(self,l0,r0,val,mid+1,r,rs);
    };

    for(int i = 1;i <= q;++i){
        int op,tp,x,y;
        ll w;
        cin >> op >> tp >> x >> y >> w;
        w = M(w);
        if(op == 0){
            if(tp == 0){
                if(vert[x][y][0])upd(upd,lstv0[x][y],i-1,{op,tp,x,y,vert[x][y][0]},0,q,1);
                lstv0[x][y] = i;
                vert[x][y][0] = w;
            }else{
                if(hori[x][y][0])upd(upd,lsth0[x][y],i-1,{op,tp,x,y,hori[x][y][0]},0,q,1);
                lsth0[x][y] = i;
                hori[x][y][0] = w;
            }
        }else{
            if(tp == 0){
                if(vert[x][y][1])upd(upd,lstv1[x][y],i-1,{op,tp,x,y,vert[x][y][1]},0,q,1);
                lstv1[x][y] = i;
                vert[x][y][1] = w;
            }else{
                if(hori[x][y][1])upd(upd,lsth1[x][y],i-1,{op,tp,x,y,hori[x][y][1]},0,q,1);
                lsth1[x][y] = i;
                hori[x][y][1] = w;
            }
        }
    }
    for(int i = 0;i < n - 1;++i){
        for(int j = 0;j < m;++j){
            if(vert[i][j][0])upd(upd,lstv0[i][j],q,{0,0,i,j,vert[i][j][0]},0,q,1);
            if(vert[i][j][1])upd(upd,lstv1[i][j],q,{1,0,i,j,vert[i][j][1]},0,q,1);
        }
    }
    for(int i = 0;i < n;++i){
        for(int j = 0;j < m - 1;++j){
            if(hori[i][j][0])upd(upd,lsth0[i][j],q,{0,1,i,j,hori[i][j][0]},0,q,1);
            if(hori[i][j][1])upd(upd,lsth1[i][j],q,{1,1,i,j,hori[i][j][1]},0,q,1);
        }
    }

    auto ers = [&](int u) -> void {
        int sum = M(dsu.sum[u] + dsu.sum[u^1]);
        add(val,-sum);
    };
    auto ins = [&](int u) -> void {
        int sum = M(dsu.sum[u] + dsu.sum[u^1]);
        add(val,sum);
    };

    auto merge = [&](int u,int v) -> int {
        int fu = dsu.find(u),fv = dsu.find(v);
        if(fu == fv)return 0;
        tot -= 1;
        return dsu.merge(fu,fv,stk);
    };

    auto findans = [&](auto &&self,int l,int r,int idx) -> void {
        int sz = stk.size();
        int flag = 1;
        stk.push_back({3,0,tot});
        stk.push_back({4,0,val});
        for(auto [op,tp,x,y,w] : info[idx]){
            if(op == 0){
                int u,v;
                int w1 = -w,w2 = w;
                if(tp == 0){
                    u = id(x,y-1),v = id(x,y);
                }else{
                    u = id(x-1,y),v = id(x,y);
                }
                if(!u)w1 = 0;
                if(!v)w2 = 0;
                u = dsu.find(u<<1|1);
                v = dsu.find(v<<1|1);
                stk.push_back({1,u,dsu.sum[u]});
                stk.push_back({1,v,dsu.sum[v]});
                if((u ^ v) > 1){
                    ers(u);
                    ers(v);
                    add(dsu.sum[u],w1);
                    add(dsu.sum[v],w2);
                    ins(u);
                    ins(v);
                }else{
                    ers(u);
                    add(dsu.sum[u],w1);
                    add(dsu.sum[v],w2);
                    ins(u);
                }
            }else{
                int u,v;
                if(tp == 0){
                    u = id(x,y-1),v = id(x,y);
                }else{
                    u = id(x-1,y),v = id(x,y);
                }
                if(w == 1){
                    int fx = dsu.find(u<<1);
                    int fy = dsu.find(v<<1);
                    if(fx ^ fy){
                        ers(fx);
                        ers(fy);
                        int f;
                        f = merge(u<<1,v<<1);
                        merge(u<<1|1,v<<1|1);
                        ins(f);
                    }
                }else{
                    int fx = dsu.find(u<<1);
                    int fy = dsu.find(v<<1|1);
                    if(dsu.find(fx) ^ dsu.find(fy)){
                        ers(fx);
                        ers(fy);
                        int f;
                        f = merge(u<<1,v<<1|1);
                        merge(u<<1|1,v<<1);
                        ins(f);
                    }
                }
                if(dsu.find(u<<1) == dsu.find(u<<1|1) || dsu.find(v<<1) == dsu.find(v<<1|1)){
                    flag = 0;
                    break;
                }
            }
        }
        if(flag){
            if(l == r){
                cout << qp(2,tot/2-1) << ' ';
                cout << M(1ll * (dsu.sum[dsu.find(0)] + val - dsu.sum[dsu.find(1)]) * qp(2,tot/2-2));
                cout << '\n';
            }else{
                int mid = (l + r) >> 1;
                self(self,l,mid,ls);
                self(self,mid+1,r,rs);
            }
        }else{
            for(int i = l;i <= r;++i){
                cout << "0 0\n";
            }
        }
        while(stk.size() > sz){
            auto [op,u,w] = stk.back();
            if(op == 0){
                dsu.pre[u] = w;
            }else if(op == 1){
                dsu.sum[u] = w;
            }else if(op == 2){
                dsu.h[u] = w;
            }else if(op == 3){
                tot = w;
            }else if(op == 4){
                val = w;
            }
            stk.pop_back();
        }
    };
    findans(findans,0,q,1);
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int _qaq = 1;
    cin >> _qaq;
    while(_qaq--){
        solve();
    }
    return 0;
}