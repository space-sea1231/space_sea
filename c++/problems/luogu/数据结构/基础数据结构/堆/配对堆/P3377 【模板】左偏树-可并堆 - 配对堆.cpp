#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n, m;
int a[N];
struct Pairng_Heap{
    struct Node{
        int val, fa;
        int to, nxt;
        bool flag;
    }e[N];
    int Find(int x){
        if (x==e[x].fa){
            return x;
        }
        return e[x].fa=Find(e[x].fa);
    }
    int Merge(int x, int y){
        if (x==0||y==0||x==y){
            return x?x:y;
        }
        if (e[x].val>e[y].val||(e[x].val==e[y].val&&x>y)){
            swap(x, y);
        }
        e[y].nxt=e[x].to;
        e[x].to=y;
        return e[y].fa=x;
    }
    int Merges(int x){
        if (x==0){
            return 0;
        }
        e[x].fa=x;
        if (!e[x].nxt){
            return x;
        }
        int y=e[x].nxt;
        int z=e[y].nxt;
        e[x].nxt=0, e[y].nxt=0;
        e[y].fa=y;
        return Merge(Merges(z), Merge(x, y));
    }
    int Query(int x){
        if (e[x].flag){
            int fx=Find(x);
            e[fx].flag=0;
            e[fx].fa=Merges(e[fx].to);
            return e[fx].val;
        }else{
            return -1;
        }
    }
    void Init(){
        for (int i=1; i<=n; i++){
            e[i].val=a[i];
            e[i].fa=i, e[i].flag=1;
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
            if (heap.e[x].flag&&heap.e[y].flag){
                heap.Merge(heap.Find(x), heap.Find(y));
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