#include <bits/stdc++.h>
using namespace std;
const int N=5e3+10;
const int M=2e5+10;
int sum, cnt, n, m;//基础系列
int fa[N];//并查集
struct node{
    int u, v, w;
    bool operator<(const node &a){
        return w<a.w;
    }
}e[M*2];
void add(int u, int v, int w){
    e[++cnt].u=u;
    e[cnt].v=v;
    e[cnt].w=w;
}
int find(int x){
    if (fa[x]==x){
        return x;
    }
    return fa[x]=find(fa[x]);
}
void kruskal(){
    cnt=0;
    int u, v, w;
    sort(e+1, e+m*2+1);//排序：由小到大
    for (int i=1; i<=m*2; i++){//枚举每一条边
        u=find(e[i].u);
        v=find(e[i].v);
        w=e[i].w;
        if (u==v){
            continue;
        }
        fa[u]=v;
        sum+=w;
        if (++cnt==n-1){
            printf("%d", sum);
            exit(0);
        }
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    int u, v, w;
    for (int i=1; i<=n; i++){//并查集初始化
        fa[i]=i;
    }
    for (int i=1; i<=m; i++){
        cin >> u >> v >> w;
        add(u, v, w);//建双向边
        add(v, u, w);
    }
    kruskal();//最小生成树-kruskal
    printf("orz");

    return 0;
}