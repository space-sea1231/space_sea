#include <bits/stdc++.h>
using namespace std;
const int N=1e4+10;
int n;
struct Node{
    int v, w;
    bool operator<(const Node &a){
        return w>a.w;
    }
}e[N];
struct Union_Find{
    int fa[N];
    int Find(int x){
        if (fa[x]==x){
            return x;
        }
        return fa[x]=Find(fa[x]);
    }
    int Check(int x){
        int fx=Find(fa[e[x].v]);
        if (fx>0){
            fa[fx]=Find(fa[e[x].v]-1);
            return e[x].w;
        }
        return 0;
    }
    void Init(){
        for (int i=0; i<N; i++){
            fa[i]=i;
        }
    }
}unf;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    while (cin >> n){
        unf.Init();
        for (int i=1; i<=n; i++){
            cin >> e[i].w >> e[i].v;
        }
        sort(e+1, e+n+1);
        int ans=0;
        for (int i=1; i<=n; i++){
            ans+=unf.Check(i);
        }
        printf("%d\n", ans);
    }

    return 0;
}