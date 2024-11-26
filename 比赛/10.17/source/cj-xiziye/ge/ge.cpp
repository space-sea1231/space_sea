#include<bits/stdc++.h>
#define int long long
#define pc putchar
using namespace std;
void read(int &p){
    int res=0,fh=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') fh=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') res=res*10+ch-'0',ch=getchar();
    p=res*fh;
}
void prt(int x){
    if(x<0) putchar('-'),x=-x;
    if(x>=10) prt(x/10);
    putchar(x%10+'0');
}
const int N=1e5+10;
const int inf=0x7fffffffffffffff;
const int MOD=998442353;
struct node_dijstra{
    int id,w;
    bool operator<(const node_dijstra &x)const{return w>x.w;}
};
void dijstra(int n,int s,int *head,int *nxt,int *w,int *to,int *dis){
    priority_queue<node_dijstra> pq;
    for(int i=1;i<=n;i++) dis[i]=inf;
    pq.push((node_dijstra){s,0});
    dis[s]=0;
    while(!pq.empty()){
        node_dijstra tmp=pq.top();pq.pop();
        if(dis[tmp.id]<tmp.w) continue;
        for(int i=head[tmp.id];i;i=nxt[i]){
            int v=to[i];
            if(dis[v]<tmp.w+w[i]) continue;
            dis[v]=tmp.w+w[i];
            pq.push((node_dijstra){v,dis[v]});
        }
    }
}
int T,n,m;
struct node{
    int p[20];
}a[20];
int dis(node x,node y){
    int res=0;
    for(int i=1;i<=n;i++) res+=abs(x.p[i]-y.p[i]);
    return res;
}
int sol(node x,node y){
    int res=1;
    for(int i=1;i<=n;i++) res*=abs(x.p[i]-y.p[i])%MOD;
}
int s[20];
int head[20],to[405],val[405],nxt[405],tot;
void add(int u,int v,int w){
    to[++tot]=v;
    val[tot]=w;
    nxt[tot]=head[u];
    head[u]=tot;
}
int res[205],ans=inf,cnt;
signed main(){
    freopen("ge.in","r",stdin);
    freopen("ge.out","w",stdout);
    read(T);
    while(T--){
        read(n);read(m);
        for(int i=1;i<=m;i++){
            for(int j=1;j<=n;j++) read(a[i].p[j]);
        }
        for(int i=1;i<=m;i++){
            for(int j=1;j<=m;j++){
                if(i==j) continue;
                int w=dis(a[i],a[j]);
                cout<<i<<" "<<j<<" "<<w<<"\n";
                add(i,j,w);
            }
        }
        for(int i=1;i<=m;i++){
            read(s[i]);
            if(s[i]==0) continue;
            // cout<<i<<"\n";
            int mx=0;
            dijstra(m,i,head,nxt,val,to,res);
            // for(int j=1;j<=n;j++) prt(res[j]),pc(' ');pc('\n');
            for(int j=1;j<=n;j++) mx=max(mx,res[j]);
            if(mx==ans) cnt++;
            if(mx<ans) ans=mx,cnt=1;
        }
        prt(ans);
        pc(' ');
        prt(cnt);
        pc('\n');
    }
    return 0;
}