#include<queue>
#include<cstdio>
#include<iostream>
#include<cstring>
#define MAXM 5000100
#define MAXN 1001000
using namespace std;
int to[MAXM],nxt[MAXM],w[MAXM],cost[MAXM],head[MAXN];
int n,m,S,T,ansl=0,ansc=0;
int cnt=-1;
int pre1[MAXN],pre2[MAXN],low[MAXN],dis[MAXN];
void link(int a,int b,int c,int d){
    cnt++;
    nxt[cnt]=head[a];
    w[cnt]=c;
    cost[cnt]=d;
    to[cnt]=b;
    head[a]=cnt;
    cnt++;
    nxt[cnt]=head[b];
    w[cnt]=0;
    cost[cnt]=-d;
    to[cnt]=a;
    head[b]=cnt;
}
bool spfa(){
    queue<int>q;
    fill(dis,dis+MAXN,66666666);
    int vis[MAXN];
    memset(vis,0,sizeof(vis));
    q.push(S);
    dis[S]=0;
    vis[S]=1;
    low[S]=66666666;
    while(!q.empty()){
    int now=q.front();
    vis[now]=0;
    q.pop();
    for(int i=head[now];i!=-1;i=nxt[i]){
        if (w[i]>0&&cost[i]+dis[now]<dis[to[i]]){
            dis[to[i]]=dis[now]+cost[i];
            low[to[i]]=min(low[now],w[i]);
            pre1[to[i]]=now;
            pre2[to[i]]=i;
            if (!vis[to[i]]){
                vis[to[i]]=1;
                q.push(to[i]);
            }
        }
    }
    }
    return dis[T]!=66666666;
}
void work(){
    while(spfa()){
        int now=T;
        while(now!=S){
            int y=pre2[now];
            w[y]-=low[T];
            w[y^1]+=low[T];
            now=pre1[now];
        }
        ansl+=low[T];
        ansc+=low[T]*dis[T];
    }
}
int num(int a,int b){
    return (a-1)*n+b;
}
int main(){
    int K,A,B,C;
    memset(head,-1,sizeof(head));
    cin>>n>>K>>A>>B>>C;
    S=0;T=MAXN-1;
    link(S,num(1,1),1,0);
    for(int i=0;i<=K;i++)
        link(num(n,n)+10001*i,T,1,0);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            int a;
            scanf("%d",&a);
            if (a)for(int k=1;k<=K;k++)link(num(i,j)+k*10001,num(i,j),1,A);
            for(int k=0;k<K;k++){
                if (a&&k)break;
                if (i+1<=n)link(num(i,j)+k*10001,num(i+1,j)+(k+1)*10001,MAXM,0);
                if (j+1<=n)link(num(i,j)+k*10001,num(i,j+1)+(k+1)*10001,MAXM,0);
                if (i-1>0)link(num(i,j)+k*10001,num(i-1,j)+(k+1)*10001,MAXM,B);
                if (j-1>0)link(num(i,j)+k*10001,num(i,j-1)+(k+1)*10001,MAXM,B);
            }
            link(num(i,j)+K*10001,num(i,j),1,A+C);
        }
    }
    work();
    cout<<ansc<<endl;
    return 0;
}

