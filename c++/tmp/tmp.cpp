#include<bits/stdc++.h>
using namespace std;
#define int unsigned long long 
const int N=1e6+5;
int T,n,m,t[N],in[N],tot,head[N];
struct edge{
    int to,next,w;
}e[N*2];
void add(int u,int v,int w){
    e[++tot].to=v;
    e[tot].next=head[u];
    e[tot].w=w;
    head[u]=tot;
}

int dfs(int u){
    int res=0;
    if (t[u])   return t[u];
    for (int i=head[u];i;i=e[i].next){
        int v=e[i].to,w=e[i].w;
        int sn=dfs(v);
        res+=w*sn;
        // cout<<u<<" "<<v<<" "<<w<<" "<<sn<<"\n";
    }
    t[u]=res;
    // cout<<u<<" "<<t[u]<<"\n";
    return res;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>m;
        memset(in,0,sizeof(in));
        memset(t,0,sizeof(t));
        memset(head,0,sizeof(head));
        memset(e,0,sizeof(e));
        tot=0;
        for (int i=1,p=0;i<=n;i++){
            cin>>p;
            if (!p){
                cin>>t[i];
            }else{
                int len=0;
                cin>>len;
                for (int j=1;j<=len;j++){
                    int tm,x;
                    cin>>tm>>x;
                    add(i,x,tm);
                    in[x]++;
                }
            }
        }
        int root=0;
        for (int i=1;i<=n;i++){
            if (in[i]==0){
                root=i;
                // cout<<i<<"\n";
                dfs(root);
            }
        }
        int ans=t[m],maxx=0;
        for (int i=head[m];i;i=e[i].next){
            int v=e[i].to,w=e[i].w;
            maxx=max(maxx,w*t[v]);
        }
        if (ans-maxx>(int)(1e9)){
            cout<<"Impossible\n";
            continue;
        }
        cout<<ans-maxx<<"\n";
    }
    return 0;
}