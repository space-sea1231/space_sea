#include <bits/stdc++.h>
using namespace std;
const int N=4e4+10;
const int INF=0x7fffffff;
int n, ans;
struct Treap{
    int root, num;
    struct Node{
        int l, r;
        int vis, val;
        int cnt;
    }e[N<<1];
    int New(int val){
        e[++num].val=val;
        e[num].vis=rand();
        e[num].cnt=1;
        return num;
    }
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
    void Insert(int &x, int val){
        if (x==0){
            x=New(val);
            return ;
        }
        if (e[x].val==val){
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
    int Pre(int x, int val){
        if (x==0){
            return -INF;
        }
        if (e[x].val==val){
            return val;
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
        if (e[x].val==val){
            return val;
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
        int a, sum_pre=INF, sum_nxt=INF;
        cin >> a;
        sum_pre=tree.Pre(tree.root, a);
        sum_nxt=tree.Nxt(tree.root, a);
        if (sum_pre==-INF&&sum_nxt==INF){
            ans+=a;
        }else if (sum_pre==-INF){
            ans+=abs(sum_nxt-a);
        }else if (sum_nxt==INF){
            ans+=abs(sum_pre-a);
        }else{
            ans+=min(abs(sum_nxt-a), abs(sum_pre-a));
        }
        tree.Insert(tree.root, a);
    }
    printf("%d\n", ans);

    return 0;
}