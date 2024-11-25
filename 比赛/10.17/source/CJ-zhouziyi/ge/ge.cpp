#include<bits/stdc++.h>
#define int long long
#define N 1000005
using namespace std;
int n,m,a[N],res=2e18;
bool vis[N];
unordered_map<int,int> mp;
void dfs(int u,int cnt,int sum){
    // cout<<u<<" "<<cnt<<" "<<sum<<endl;
    if(cnt==m){
        mp[sum]++;
        res=min(res,sum);
        return ;
    }
    for(int i=1;i<=m;i++){
        if(vis[i]) continue;
        vis[i]=1;
        dfs(i,cnt+1,sum+abs(a[u]-a[i]));
        vis[i]=0;
    }
}
signed main(){
    freopen("ge.in","r",stdin);
    freopen("ge.out","w",stdout);
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin>>T;
    while(T--){
        cin>>n>>m;
        for(int i=1;i<=m;i++){
            cin>>a[i];
        }
        res=2e18;
        for(int i=1;i<=m;i++){
            int x;
            cin>>x;
            memset(vis,0,sizeof(vis));
            if(x){
                vis[i]=1;
                dfs(i,1,0);
            }
        }
        cout<<res<<" "<<mp[res]<<"\n";
    }
}