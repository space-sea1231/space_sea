#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;
struct Edge{
    Edge *next;
    int v,w;
    ~Edge(){
        if(next) delete next;
    }
};
struct Node{
    Edge *head;
    int dep,nodp;
}node[1000005];
int n;
int fa[1000005][25];
int cost[1000005];
int LCA(int x,int y){
    if(node[x].nodp<node[y].nodp){
        swap(x,y);
    }
    for(int i=24;i>=0;i--){
        if(node[x].nodp-(1<<i)>=node[y].nodp){
            x=fa[x][i];
        }
    }
    if(x==y) return x;
    for(int i=24;i>=0;i--){
        if(fa[x][i]!=fa[y][i]){
            x=fa[x][i];
            y=fa[y][i];
        }
    }
    return fa[x][0];
}
void Add(int u,int v,int w=1){
    Edge *tmp=new Edge;
    tmp->v=v;
    tmp->w=w;
    tmp->next=node[u].head;
    node[u].head=tmp;
}
void Init(int now,int f){
    fa[now][0]=f;
    for(Edge *i=node[now].head;i;i=i->next){
        if(i->v!=f){
            node[i->v].dep=node[now].dep+i->w;
            node[i->v].nodp=node[now].nodp+1;
            Init(i->v,now);
        }
    }
}
void Multiply(){
    for(int j=1;j<20;j++){
        for(int i=1;i<=n;i++){
            fa[i][j]=fa[fa[i][j-1]][j-1];
        }
    }
}
int m,k;
int h[1000005];
vector<int> lsh;
void dfs(int now,int fa){
    for(Edge *i=node[now].head;i;i=i->next){
        if(i->v!=fa){
            dfs(i->v,now);
            cost[now]+=cost[i->v];
        }
    }
}
int dp[805][805];
int minn[805];
int upper,mid;
void cfs(int now,int fa){
    for(int i=0;i<upper;i++){
        if(lsh[h[now]]<=lsh[i]+mid&&lsh[h[now]]>=lsh[i]){
            dp[now][i]=0;
        }
        else{
            dp[now][i]=1e9;
        }
    }
    minn[now]=h[now];
    for(Edge *i=node[now].head;i;i=i->next){
        if(i->v!=fa){
            cfs(i->v,now);
            for(int j=0;j<=h[now];j++){
                dp[now][j]+=min(dp[i->v][j],dp[i->v][minn[i->v]]+cost[i->v]);
            }
        }
    }
    for(int i=0;i<=h[now];i++){
        dp[now][i]=min(dp[now][i],1000000000);
        if(dp[now][i]<dp[now][minn[now]]){
            minn[now]=i;
        }
    }
}
bool check(){
    cfs(1,0);
    // for(int i=1;i<=n;i++){
    //     for(int j=0;j<upper;j++){
    //         printf("dp[%d][%d]=%d\n",i,lsh[j],dp[i][j]);
    //     }
    // }
    for(int i=0;i<upper;i++){
        if(dp[1][i]<=k) return 1;
    }
    return 0;
}
void Work(){
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++){
        scanf("%d",&h[i]);
        lsh.push_back(h[i]);
    }
    sort(lsh.begin(),lsh.end());
    auto tp=unique(lsh.begin(),lsh.end());
    upper=tp-lsh.begin();
    for(int i=1;i<=n;i++){
        h[i]=lower_bound(lsh.begin(),tp,h[i])-lsh.begin();
    }
    for(int i=1;i<n;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        Add(u,v);
        Add(v,u);
    }
    Init(1,0);
    Multiply();
    for(int i=1;i<=m;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        cost[u]++;
        cost[v]++;
        cost[LCA(u,v)]-=2;
    }
    dfs(1,0);
    int l=0,r=1e9,ans;
    while(l<=r){
        mid=l+r>>1;
        // printf("Debug:%d\n",mid);
        if(check()){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    printf("%d\n",ans);
}
signed main(){
    int t=1;
    // scanf("%d",&t);
    while(t--){
        Work();
    }
    return 0;
}
/*
4 3
1 2
1 3
2 4
2 3
3 4
3 3
*/