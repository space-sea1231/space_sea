#include <bits/stdc++.h>
using namespace std;
const int N=2e4+10;
const int M=1e5+10;
int n, m;
int fa[N], vis[N];
struct Node{
    int x, y, z;
    bool operator<(const Node &a){
        return z>a.z;
    }
}e[M];
void Init(){
    for (int i=1; i<=n; i++){
        fa[i]=i;
    }
}
int Find(int x){
    if (fa[x]==x){
        return x;
    }
    return fa[x]=Find(fa[x]);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m;
    Init();
    for (int i=1; i<=m; i++){
        cin >> e[i].x >> e[i].y >> e[i].z;
    }
    sort(e+1, e+m+1);
    int x, y, z;
    for (int i=1; i<=m; i++){
        x=Find(e[i].x), y=Find(e[i].y), z=e[i].z;
        if (x==y){
            printf("%d\n", z);
            return 0;
        }
        if (!vis[x]){
            vis[x]=y;
        }else{
            fa[Find(vis[x])]=y;
        }
        if (!vis[y]){
            vis[y]=x;
        }else{
            fa[Find(vis[y])]=x;
        }
    }
    printf("0\n");

    return 0;
}