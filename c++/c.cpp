#include <bits/stdc++.h>
using namespace std;
const int N=5e3+10;
const int M=2e5+10;
int n, m;
int sum, ans;
struct Kruskal{
    int cnt;
    int head[N];
    int to[M<<1], nxt[M<<1], val[M<<1];
    struct Node{
        int u, v, w;
        bool operator<(const Node &a)const{
            return w>a.w;
        }
    }e[M<<1];
    struct Union_Find{
        int fa[N];
        int Find(int x){
            if (x==fa[x]){
                return x;
            }
            return fa[x]=Find(fa[x]);
        }
        Union_Find(){
            for (int i=1; i<N; i++){
                fa[i]=i;
            }
        }
    }uf;
    void Add(int u, int v, int w){
        e[++cnt].u=u;
        e[cnt].v=v;
        e[cnt].w=w;
    }
    void kruskal(){
        sort(e+1, e+m+1);
        for (int i=1; i<=m; i++){
            int u=e[i].u, v=e[i].v, w=e[i].w;
            int fu=uf.Find(u), fv=uf.Find(v);
            if (fu!=fv){
                uf.fa[fu]=fv;
                Insert()
            }
        }
    }
}graph;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m;
    for (int i=1; i<=m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        graph.Add(u, v, w);
    }
    graph.kruskal();
    if (sum+1==n){
        printf("%d\n", ans);
    }else{
        printf("orz\n");
    }
    
    return 0;
}