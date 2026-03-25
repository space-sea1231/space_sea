#include <bits/stdc++.h>
using namespace std;
const int N=3e5+10;
int n, m;
int ttt;
struct Treap{
    int root, num=0;
    int cnt_in=0, cnt_out;
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
                cnt_out+=e[x].cnt-1;
                e[x].cnt=1;
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
    void Find(int &x, int val){
        if (x==0){
            return ;
        }
        Find(e[x].l, val);
        Find(e[x].r, val);
        e[x].val+=val;
        if (e[x].val<m){
            Remove(x, e[x].val);
            cnt_out++;
        }
    }
    int Rank_Val(int x, int rank){
        if (x==0){
            return 0;
        }
        if (e[e[x].r].size>=rank){
            return Rank_Val(e[x].r, rank);
        }
        if (e[e[x].r].size+e[x].cnt>=rank){
            return e[x].val;
        }
        return Rank_Val(e[x].l, rank-e[e[x].r].size-e[x].cnt);
    }
}tree;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m;
    for (int i=1; i<=n; i++){
        char opt;
        int x;
        cin >> opt >> x;
        if (opt=='I'){
            if (x>=m){
                tree.Insert(tree.root, x);
                tree.cnt_in++;
            }
        }
        if (opt=='A'){
            tree.Find(tree.root, x);
        }
        if (opt=='S'){
            tree.Find(tree.root, -x);
        }
        if (opt=='F'){
            if (x>tree.cnt_in-tree.cnt_out){
                printf("-1\n");
            }else{
                printf("%d\n", tree.Rank_Val(tree.root, x));
            }
        }
    }
    printf("%d\n", tree.cnt_out);

    return 0;
}