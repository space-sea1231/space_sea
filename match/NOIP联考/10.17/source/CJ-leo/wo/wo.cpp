#include<bits/stdc++.h>
using namespace std;
void file_init(){
#ifndef ONLINE_JUDGE
    freopen("wo.in","r",stdin);
    freopen("wo.out","w",stdout);
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
const int N=1e6+10;
int n;
int p[N<<1];
void read(){
    cin>>n;
    for(int i=1;i<=(n<<1);i++){
        cin>>p[i];
    }
    return ;
}
bool vis[N<<1];
void init(){
    for(int i=1;i<=(n<<1);i++){
        vis[i]=0;
    }
    for(int i=1;i<=(n<<1);i++){
        vis[p[i]]=1;
    }
    return ;
}
int mx,ans;
const int mod=998244353;
void dfs(int x,int cnt,int val){
    if(x==(n<<1|1)){
        if(val>mx){
            mx=val;
            ans=cnt;
        }else if(val==mx){
            ans+=cnt;
            if(ans>=mod){
                ans-=mod;
            }
        }
        return ;
    }
    if(p[x]&&p[x+1]){
        dfs(x+2,cnt,val+abs(p[x]-p[x+1]));
    }else if(p[x]){
        for(int i=1;i<=(n<<1);i++){
            if(!vis[i]){
                vis[i]=1;
                p[x+1]=i;
                dfs(x+2,cnt,val+abs(p[x]-p[x+1]));
                p[x+1]=0;
                vis[i]=0;
            }
        }
    }else if(p[x+1]){
        for(int i=1;i<=(n<<1);i++){
            if(!vis[i]){
                vis[i]=1;
                p[x]=i;
                dfs(x+2,cnt,val+abs(p[x]-p[x+1]));
                p[x]=0;
                vis[i]=0;
            }
        }
    }else{
        cnt<<=1;
        if(cnt>=mod){
            cnt-=mod;
        }
        for(int i=1;i<=(n<<1);i++){
            if(vis[i]){
                continue;
            }
            vis[i]=1;
            p[x]=i;
            for(int j=i+1;j<=(n<<1);j++){
                if(vis[j]){
                    continue;
                }
                vis[j]=1;
                p[x+1]=j;
                dfs(x+2,cnt,val+abs(p[x]-p[x+1]));
                p[x+1]=0;
                vis[j]=0;
            }
            p[x]=0;
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
        mx=ans=0;
        dfs(1,1,0);
        cout<<ans<<"\n";
    }
    return 0;
}