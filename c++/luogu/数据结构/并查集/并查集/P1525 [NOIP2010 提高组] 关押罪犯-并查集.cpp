#include <bits/stdc++.h>
using namespace std;
const int N=2e4+10;
const int M=1e5+10;
int n, m, fa[N], vis[N];
struct node{
    int u, v, w;
    bool operator < (const node &a){
        return w>a.w;
    }
}e[M];
int find(int x){
    if (fa[x]==x){
        return x;
    }
    return fa[x]=find(fa[x]);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    int u, v, w;
    for (int i=1; i<=n; i++){
        fa[i]=i;
    }
    for (int i=1; i<=m; i++){
        cin >> u >> v >> w;
        e[i].u=u, e[i].v=v, e[i].w=w;
    }
    sort(e+1, e+m+1);
    for (int i=1; i<=m; i++){
        u=find(fa[e[i].u]), v=find(e[i].v), w=e[i].w;
        if (u==v){
            printf("%d", w);
            return 0;
        }
        if (!vis[u]){
            vis[u]=v;
        }else{
            fa[find(vis[u])]=v;
        }
        if (!vis[v]){
            vis[v]=u;
        }else{
            fa[find(vis[v])]=u;
        }
    }
    printf("0");
    
    return 0;
}