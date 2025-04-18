#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
const int INF=0x7fffffff;
int n;
struct Treap{
    int num=0, root;
    struct Node{
        int l, r;
        int vis, val;
        int cnt, size;
    }e[N<<1];
    void Update(int x){
        e[x].size=e[e[x].l].size+e[e[x].r].size+e[x].cnt;
    }
    void Zig(int &x){
        int y=e[x].l;
        e[x].l=e[y].r;
        e[y].r=x, x=y;
        Update(e[x].r);
        Update(x);
    }
    void Zag(int &x){
        int y=e[x].r;
        e[x].r=e[y].l;
        e[y].l=x, x=y;
        Update(e[x].l);
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
        Update(x);
    }
    void Remove(int &x, int val){
        if (x==0){
            return ;
        }
        if (val==e[x].val){
            if (e[x].cnt>1){
                e[x].cnt--;
                Update(x);
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
            }
        }else{
            if (val<e[x].val){
                Remove(e[x].l, val);
            }else{
                Remove(e[x].r, val);
            }
        }
        Update(x);
    }
    int Val_Rank(int x, int val){
        if (x==0){
            return 1;
        }
        if (val==e[x].val){
            return e[e[x].l].size+1;
        }
        if (val<e[x].val){
            return Val_Rank(e[x].l, val);
        }else{
            return Val_Rank(e[x].r, val)+e[e[x].l].size+e[x].cnt;
        }
    }
    int Rank_Val(int x, int rank){
        if (x==0){
            return INF;
        }
        if (e[e[x].l].size>=rank){
            return Rank_Val(e[x].l, rank);
        }
        if (e[e[x].l].size+e[x].cnt>=rank){
            return e[x].val;
        }
        return Rank_Val(e[x].r, rank-e[e[x].l].size-e[x].cnt);
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
}tree;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n;
    for (int i=1; i<=n; i++){
        int opt, x;
        cin >> opt >> x;
        if (opt==1){
            tree.Insert(tree.root, x);
        }
        if (opt==2){
            tree.Remove(tree.root, x);
        }
        if (opt==3){
            printf("%d\n", tree.Val_Rank(tree.root, x));
        }
        if (opt==4){
            printf("%d\n", tree.Rank_Val(tree.root, x));
        }
        if (opt==5){
            printf("%d\n", tree.Pre(tree.root, x));
        }
        if (opt==6){
            printf("%d\n", tree.Nxt(tree.root, x));
        }
    }
    
    return 0;
}