#include <bits/stdc++.h>
using namespace std;
const int N=5e5+10;
const int M=1e6+10;
const int INF=0x7fffffff;
int n;
struct Treap_Side{
    int root, num;
    struct Val{
        int l, r;
        bool operator<(const Val &a)const{
            return l<a.l;
        }
        bool operator>(const Val &a)const{
            return l>a.l;
        }
        bool operator==(const Val &a)const{
            return l==a.l&&r==a.r;
        }
    };
    struct Node{
        Val val;
        int vis;
        int lson, rson;
        int cnt, size;
    }e[N<<1];
    void Update(int x){
        e[x].size=e[e[x].lson].size+e[e[x].rson].size+e[x].cnt;
    }
    void Zig(int &x){
        int y=e[x].lson;
        e[x].lson=e[y].rson;
        e[y].rson=x, x=y;
        Update(e[x].rson);
        Update(x);
    }
    void Zag(int &x){
        int y=e[x].rson;
        e[x].rson=e[y].lson;
        e[y].lson=x, x=y;
        Update(e[x].lson);
        Update(x);
    }
    int New(Val val){
        e[++num].val=val;
        e[num].vis=rand();
        e[num].size=1;
        e[num].cnt=1;
        return num;
    }
    void Insert(int &x, Val val){
        if (x==0){
            x=New(val);
            Update(x);
            return ;
        }
        if (val<e[x].val){
            Insert(e[x].lson, val);
            if (e[x].vis<e[e[x].lson].vis){
                Zig(x);
            }
        }else{
            Insert(e[x].rson, val);
            if (e[x].vis<e[e[x].rson].vis){
                Zag(x);
            }
        }
        Update(x);
    }
    void Delete(int &x, Val val){
        if (x==0){
            return ;
        }
        if (val==e[x].val){
            if (e[x].lson||e[x].rson){
                if (e[x].rson==0||e[e[x].lson].vis>e[e[x].rson].vis){
                    Zig(x);
                    Delete(e[x].rson, val);
                }else{
                    Zag(x);
                    Delete(e[x].lson, val);
                }
            }else{
                x=0;
            }
        }else{
            if (val<e[x].val){
                Delete(e[x].lson, val);
            }else{
                Delete(e[x].rson, val);
            }
        }
        Update(x);
    }
    int Pre(int x, Val val){
        if (x==0){
            return -INF;
        }
        if (e[x].val<val){
            return max(e[x].val.l, Pre(e[x].rson, val));
        }else{
            return Pre(e[x].lson, val);
        }
    }
    int Nxt(int x, Val val){
        if (x==0){
            return INF;
        }
        if (e[x].val>val){
            return min(e[x].val.r, Nxt(e[x].lson, val));
        }else{
            return Nxt(e[x].rson, val);
        }
    }
}Side;
struct Treap_Val{
    int num=0, root;
    struct Node{
        int lson, rson;
        int vis, val;
        int cnt, size;
    }e[N<<1];
    void Update(int x){
        e[x].size=e[e[x].lson].size+e[e[x].rson].size+e[x].cnt;
    }
    void Zig(int &x){
        int y=e[x].lson;
        e[x].lson=e[y].rson;
        e[y].rson=x, x=y;
        Update(e[x].rson);
        Update(x);
    }
    void Zag(int &x){
        int y=e[x].rson;
        e[x].rson=e[y].lson;
        e[y].lson=x, x=y;
        Update(e[x].lson);
        Update(x);
    }
    int New(int val){
        e[++num].val=val;
        e[num].vis=rand();
        e[num].size=1;
        e[num].cnt=1;
        return num;
    }
    void Insert(int &x, int val){
        if (x==0){
            x=New(val);
            Update(x);
            return ;
        }
        if (val==e[x].val){
            e[x].cnt++;
            Update(x);
            return ;
        }
        if (val<e[x].val){
            Insert(e[x].lson, val);
            if (e[x].vis<e[e[x].lson].vis){
                Zig(x);
            }
        }else{
            Insert(e[x].rson, val);
            if (e[x].vis<e[e[x].rson].vis){
                Zag(x);
            }
        }
        Update(x);
    }
    void Delete(int &x, int val){
        if (x==0){
            return ;
        }
        if (val==e[x].val){
            if (e[x].cnt>1){
                e[x].cnt--;
                Update(x);
                return ;
            }
            if (e[x].lson||e[x].rson){
                if (e[x].rson==0||e[e[x].lson].vis>e[e[x].rson].vis){
                    Zig(x);
                    Delete(e[x].rson, val);
                }else{
                    Zag(x);
                    Delete(e[x].lson, val);
                }
            }else{
                x=0;
            }
        }else{
            if (val<e[x].val){
                Delete(e[x].lson, val);
            }else{
                Delete(e[x].rson, val);
            }
        }
        Update(x);
    }
    int Min(){
        int x=root, ans=INF;
        while (x){
            ans=min(ans, e[x].val);
            if (e[x].lson){
                x=e[x].lson;
            }else{
                x=e[x].rson;
            }
        }
        return ans;
    }
}Val, Cnm;
int main(){
    freopen("stone.in", "r", stdin);
    freopen("stone.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n;
    for (int i=1; i<=n; i++){
        char opt;
        int l, r;
        cin >> opt >> l >> r;
        if (opt=='A'){
            Side.Insert(Side.root, {l, r});
            Cnm.Insert(Cnm.root, r-l);
            int L=Side.Pre(Side.root, {l, r});
            int R=Side.Nxt(Side.root, {l, r});
            if (L!=-INF){
                Val.Insert(Val.root, r-L);
            }
            if (R!=INF){
                Val.Insert(Val.root, R-l);
            }
        }
        if (opt=='R'){
            int L=Side.Pre(Side.root, {l, r});
            int R=Side.Nxt(Side.root, {l, r});
            Cnm.Delete(Cnm.root, r-l);
            Side.Delete(Side.root, {l, r});
            if (L!=-INF){
                Val.Delete(Val.root, r-L);
            }
            if (R!=INF){
                Val.Delete(Val.root, R-l);
            }
        }
        if (Val.root){
            printf("%d\n", Val.Min());
        }else{
            printf("%d\n", Cnm.Min());
        }
    }

    return 0;
}