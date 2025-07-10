#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
const int INF=0x7fffffff;
int n;
struct Treap{
    int num=0, root=0;
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