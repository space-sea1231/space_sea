#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n, m;
int a[N];
struct Leftist_Tree{
    struct Node{
        int dist, val;
        int lson, rson;
        int fa, flag;
        int id;
        bool operator<(const Node &a){
            if (val==a.val){
                return id<a.id;
            }
            return val<a.val;
        }
    }e[N];
    int Find(int x){
        if (e[x].fa==x){
            return x;
        }
        return e[x].fa=Find(e[x].fa);
    }
    int &Rson(int x){
        int rson=e[x].rson, lson=e[x].lson;
        if (e[rson].dist<e[lson].dist||(e[rson].dist==e[lson].dist&&e[lson].id<e[rson].id)){
            return e[x].rson;
        }else{
            return e[x].lson;
        }
    }
    int Merge(int x, int y){
        if (!x||!y){
            return x|y;
        }
        if (e[y]<e[x]){
            swap(x, y);
        }
        int &rson=Rson(x);
        rson=Merge(rson, y);
        e[x].dist=e[rson].dist+1;
        return e[rson].fa=x;
    }
    void PushUp(int x){
        if (!x){
            return ;
        }
        if (e[x].dist!=e[Rson(x)].dist+1){
            e[x].dist=e[Rson(x)].dist+1;
            PushUp(e[x].fa);
        }
    }
    void Merges(int x){
        int y=Merge(e[x].lson, e[x].rson);
        e[y].fa=e[x].fa;
        if (e[e[x].fa].lson==x){
            e[e[x].fa].lson=y;
        }
        if (e[e[x].fa].rson==x){
            e[e[x].fa].rson=y;
        }
        PushUp(e[x].fa);
        e[x].fa=y;
        e[e[x].lson].fa=y;
        e[e[x].rson].fa=y;
    }
    int Query(int x){
        if (e[x].flag){
            int fx=Find(x);
            e[fx].flag=0;
            Merges(fx);
            return e[fx].val;
        }else{
            return -1;
        }
    }
    void Init(){
        e[0].dist=-1;
        for (int i=1; i<=n; i++){
            e[i].val=a[i], e[i].flag=1;
            e[i].fa=i, e[i].id=i;
        }
    }
}heap;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m;
    for (int i=1; i<=n; i++){
        cin >> a[i];
    }
    heap.Init();
    for (int i=1; i<=m; i++){
        int opt;
        cin >> opt;
        if (opt==1){
            int x, y;
            cin >> x >> y;
            int fx=heap.Find(x);
            int fy=heap.Find(y);
            if (heap.e[x].flag&&heap.e[y].flag&&fx!=fy){
                heap.Merge(fx, fy);
            }
        }
        if (opt==2){
            int x;
            cin >> x;
            printf("%d\n", heap.Query(x));
        }
    }

    return 0;
}