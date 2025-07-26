#include<bits/stdc++.h>
using namespace std;
void file_init(){
#ifndef ONLINE_JUDGE
    freopen("ge.in","r",stdin);
    freopen("ge.out","w",stdout);
#endif
    return ;
}
void fast_read(){
#ifndef cin
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
#endif
    return ;
}
int n,m;
const int N=20;
int p[N][N];
bool s[N];
void read(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            cin>>p[i][j];
        }
    }
    for(int i=1;i<=m;i++){
        cin>>s[i];
    }
    return ;
}
int dis[N][N];
void init(){
    for(int i=1;i<=m;i++){
        for(int j=i+1;j<=m;j++){
            for(int k=1;k<=n;k++){
                dis[i][j]+=abs(p[i][k]-p[j][k]);
                dis[j][i]+=abs(p[i][k]-p[j][k]);
            }
        }
    }
    return ;
}
const int mod=998442353;
bool vis[N];
int ans,mx;
void dfs(int cnt,int now,int val){
    if(cnt==m){
        if(val==mx){
            ans++;
        }else if(val<mx){
            mx=val;
            ans=1;
        }
        if(ans>=mod){
            ans-=mod;
        }
        return ;
    }
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            vis[i]=1;
            dfs(cnt+1,i,val+dis[now][i]);
            vis[i]=0;
        }
    }
    return ;
}
void get_ans(){
    for(int i=1;i<=n;i++){
        if(s[i]){
            vis[i]=1;
            dfs(1,i,0);
            vis[i]=0;
        }
    }
    return ;
}
int main(){
    file_init();
    fast_read();
    int t;
    cin>>t;
    while(t--){
        read();
        init();
        get_ans();
        cout<<ans<<" "<<mx<<"\n";
    }
    return 0;
}