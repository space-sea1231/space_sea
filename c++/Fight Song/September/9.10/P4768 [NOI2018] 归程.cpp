#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 2e5 + 10;
const int M = 4e5 + 10;
const int INF = 2000000000;   // > 可能的最大最短路 2e9

int n, m, Q, K, S;
int dist_[N];
bool vis[N];
vector<pair<int,int>> g[N];

struct Edge { int u, v, w, a; } e[M];
bool cmpDesc(const Edge&x, const Edge&y){ return x.a > y.a; }

// 可持久化并查集（线段树维护 fa / dep / 连通块最小 dis）
struct Node { int fa, dep, dis, l, r; } t[8000000];
int tot;
int rt[M];   // rt[k]: 合并了海拔最大的前 k 组之后的版本
int ha[M];   // ha[k]: 第 k 组的海拔（降序）
int sa[M];   // 升序去重海拔
int cntv;

int build(int l, int r){
    int p = ++tot;
    if(l==r){ t[p].fa=l; t[p].dep=0; t[p].dis=dist_[l]; t[p].l=t[p].r=0; return p; }
    int mid=(l+r)>>1;
    t[p].l=build(l,mid); t[p].r=build(mid+1,r);
    return p;
}
int qpos(int p,int l,int r,int pos){
    if(l==r) return p;
    int mid=(l+r)>>1;
    return pos<=mid ? qpos(t[p].l,l,mid,pos) : qpos(t[p].r,mid+1,r,pos);
}
int findRoot(int ver,int pos){
    int nd=qpos(ver,1,n,pos);
    if(t[nd].fa==pos) return nd;
    return findRoot(ver,t[nd].fa);
}
int setFa(int pre,int l,int r,int pos,int nf){
    int p=++tot; t[p]=t[pre];
    if(l==r){ t[p].fa=nf; return p; }
    int mid=(l+r)>>1;
    if(pos<=mid) t[p].l=setFa(t[pre].l,l,mid,pos,nf);
    else         t[p].r=setFa(t[pre].r,mid+1,r,pos,nf);
    return p;
}
int setRoot(int pre,int l,int r,int pos,int nd,int addDep){
    int p=++tot; t[p]=t[pre];
    if(l==r){ t[p].dis=nd; t[p].dep+=addDep; return p; }
    int mid=(l+r)>>1;
    if(pos<=mid) t[p].l=setRoot(t[pre].l,l,mid,pos,nd,addDep);
    else         t[p].r=setRoot(t[pre].r,mid+1,r,pos,nd,addDep);
    return p;
}
void merge(int &ver,int x,int y){
    int nx=findRoot(ver,x), ny=findRoot(ver,y);
    int fx=t[nx].fa, fy=t[ny].fa;
    if(fx==fy) return;
    if(t[nx].dep > t[ny].dep){ swap(nx,ny); swap(fx,fy); } // 小的挂到大的下面
    int nd=min(t[nx].dis, t[ny].dis);
    int addDep=(t[nx].dep==t[ny].dep)?1:0;
    ver=setFa(ver,1,n,fx,fy);        // fx 的父亲设为 fy
    ver=setRoot(ver,1,n,fy,nd,addDep); // 更新新根 fy 的最小 dis / 秩
}
void dijkstra(){
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<>> pq;
    for(int i=1;i<=n;i++){dist_[i]=INF;vis[i]=false;}
    dist_[1]=0; pq.push({0,1});
    while(!pq.empty()){
        int u=pq.top().second; pq.pop();
        if(vis[u])continue; vis[u]=true;
        for(auto&pr:g[u]){
            int v=pr.first,w=pr.second;
            if(dist_[v]>dist_[u]+w){ dist_[v]=dist_[u]+w; pq.push({dist_[v],v}); }
        }
    }
}
void solve(){
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++) g[i].clear();
    tot=0;
    for(int i=1;i<=m;i++){
        scanf("%d %d %d %d",&e[i].u,&e[i].v,&e[i].w,&e[i].a);
        g[e[i].u].push_back({e[i].v,e[i].w});
        g[e[i].v].push_back({e[i].u,e[i].w});
    }
    scanf("%d %d %d",&Q,&K,&S);
    dijkstra();

    int base=build(1,n); rt[0]=base;
    sort(e+1,e+m+1,cmpDesc);          // 海拔降序
    cntv=0; int cur=base;
    for(int i=1;i<=m;){
        int j=i, a=e[i].a;
        while(j<=m && e[j].a==a){ merge(cur,e[j].u,e[j].v); j++; }
        ++cntv; ha[cntv]=a; rt[cntv]=cur;   // 合并完这一组后存版本
        i=j;
    }
    for(int i=1;i<=cntv;i++) sa[i]=ha[cntv-i+1]; // 升序

    int lastans=0;
    for(int i=1;i<=Q;i++){
        int v0,p0; scanf("%d %d",&v0,&p0);
        int v=(int)(((ll)v0 + (ll)K*lastans - 1)%n + 1);
        int p=(int)(((ll)p0 + (ll)K*lastans)%(S+1));
        int leq = upper_bound(sa+1,sa+cntv+1,p) - (sa+1); // 海拔 <= p 的组数
        int cnt = cntv - leq;                              // 海拔 > p 的组数
        lastans = t[ findRoot(rt[cnt], v) ].dis;
        printf("%d\n", lastans);
    }
}
int main(){
    int T; scanf("%d",&T);
    while(T--) solve();
    return 0;
}