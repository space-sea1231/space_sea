#include<bits/stdc++.h>
#define int long long
#define N 1000005
#define mod 998244353
using namespace std;
int n,m,a[N],tmp[N],res;
bool vis[N];
unordered_map<int,int> mp;
void dfs(int u){
    if(u==2*n+1){
        int sum=0;
        for(int i=1;i<=n;i++) sum+=abs(tmp[2*i-1]-tmp[2*i]);
        res=max(res,sum);
        mp[sum]++;
        if(sum==22){
            for(int i=1;i<=2*n;i++) cout<<tmp[i]<<" ";
            cout<<endl;
        }
        return ;
    }
    if(a[u]!=0){
        tmp[u]=a[u];
        dfs(u+1);
        return ;
    }
    for(int i=1;i<=2*n;i++){
        if(vis[i]) continue;
        vis[i]=1;tmp[u]=i;
        dfs(u+1);
        vis[i]=0;
    }
}
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        mp.clear();
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=2*n;i++){
            cin>>a[i];
            if(a[i]) vis[a[i]]=1;
        }
        dfs(1);
        cerr<<res<<" "<<mp[res]<<"\n";
    }
}