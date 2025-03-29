#include<iostream>
#include<vector>
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
int val[1000005];
void dfs(int now,int fa){
    for(Edge *i=node[now].head;i;i=i->next){
        if(i->v!=fa){
            dfs(i->v,now);
            val[now]+=val[i->v];
        }
    }
}
void Work(){
    int m;
    scanf("%d%d",&n,&m);
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
        val[u]++;
        val[v]++;
        val[LCA(u,v)]-=2;
    }
    dfs(1,0);
    int ans=0;
    for(int i=2;i<=n;i++){
        if(val[i]==0){
            ans+=m;
        }
        if(val[i]==1){
            ans++;
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