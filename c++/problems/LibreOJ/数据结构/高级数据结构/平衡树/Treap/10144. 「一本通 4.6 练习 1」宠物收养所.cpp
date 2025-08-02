#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=8e4+10;
const int INF=(1LL<<61);
const int Mod=1e6;
int n, ans;
struct Treap{
    int num=0, root, sum=0;
    struct Node{
        int l, r;
        int vis, val;
        int cnt;
    }e[N<<1];
    void Zig(int &x){
        int y=e[x].l;
        e[x].l=e[y].r;
        e[y].r=x, x=y;
    }
    void Zag(int &x){
        int y=e[x].r;
        e[x].r=e[y].l;
        e[y].l=x, x=y;
    }
    int New(int val){
        e[++num].val=val;
        e[num].vis=rand();
        e[num].cnt=1;
        sum++;
        return num;
    }
    void Insert(int &x, int val){
        if (x==0){
            x=New(val);
            return ;
        }
        if (val==e[x].val){
            e[x].cnt++;
            return ;
        }
        if (val<e[x].val){
            Insert(e[x].l, val);
            if (e[x].vis<e[e[x].l].vis){
                Zig(x);
            }
        }else{
            Insert(e[x].r, val);
            if (e[x].vis<e[e[x].r].vis){
                Zag(x);
            }
        }
    }
    void Remove(int &x, int val){
        if (x==0){
            return ;
        }
        if (val==e[x].val){
            if (e[x].cnt>1){
                e[x].cnt--;
                sum--;
                return ;
            }
            if (e[x].l||e[x].r){
                if (e[x].r==0||e[e[x].l].vis>e[e[x].r].vis){
                    Zig(x);
                    Remove(e[x].r, val);
                }else{
                    Zag(x);
                    Remove(e[x].l, val);
                }
            }else{
                x=0;
                sum--;
            }
        }else{
            if (val<e[x].val){
                Remove(e[x].l, val);
            }else{
                Remove(e[x].r, val);
            }
        }
    }
    int Pre(int x, int val){
        if (x==0){
            return -INF;
        }
        if (e[x].val<val){
            return max(e[x].val, Pre(e[x].r, val));
        }else{
            return Pre(e[x].l, val);
        }
    }
    int Nxt(int x, int val){
        if (x==0){
            return INF;
        }
        if (e[x].val>val){
            return min(e[x].val, Nxt(e[x].l, val));
        }else{
            return Nxt(e[x].r, val);
        }
    }
}act, pas;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n;
    for (int i=1; i<=n; i++){
        bool opt;
        int x;
        cin >> opt >> x;
        if (opt){
            if (pas.sum){
                int pre=pas.Pre(pas.root, x);
                int nxt=pas.Nxt(pas.root, x);
                if (x-pre<=nxt-x){
                    pas.Remove(pas.root, pre);
                    ans=(ans+x-pre)%Mod;
                }else{
                    pas.Remove(pas.root, nxt);
                    ans=(ans+nxt-x)%Mod;
                }
            }else{
                act.Insert(act.root, x);
            }
        }else{
            if (act.sum){
                int pre=act.Pre(act.root, x);
                int nxt=act.Nxt(act.root, x);
                if (x-pre<=nxt-x){
                    act.Remove(act.root, pre);
                    ans=(ans+x-pre)%Mod;
                }else{
                    act.Remove(act.root, nxt);
                    ans=(ans+nxt-x)%Mod;
                }
            }else{
                pas.Insert(pas.root, x);
            }
        }
    }
    printf("%lld\n", ans);

    return 0;
}