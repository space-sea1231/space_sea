#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n;
struct Splay{
    int root, num;
    struct Node{
        int fa, val;
        int siz, cnt;
        int lson, rson;
    }e[N];
    void Update(int x){
        e[x].siz=e[e[x].lson].siz+e[e[x].r].siz+e[x].cnt;
    }
    void New(int x){
        e[++num].val=x;
        e[num].cnt++;
    }
    void splay(int x){
        for (int i=e[x].fa, i=e[x].fa; )
    }
    void Insert(int x){
        if (!root){
            New(x);
            Update(num);
            root=num;
            return ;
        }
        int cur=root, last=0;
        while (1){
            if (e[cur].val==x){
                e[cur].cnt++;
                Update(cur);
                Update(last);
                splay(cur);
                return ;
            }
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
            tree.Insert(x);
        }
        if (opt==2){

        }
        if (opt==3){

        }
        if (opt==4){

        }
        if (opt==5){

        }
        if (opt==6){

        }
    }
    return 0;
}