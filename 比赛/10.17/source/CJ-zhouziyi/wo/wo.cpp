#include<bits/stdc++.h>
#define int long long
#define N 1000005
#define mod 998244353
using namespace std;
int n,m,a[N],tmp[N],res;
// bool vis[N];
// unordered_map<int,int> mp;
int b[3];
// b[0] <= n
// b[1] >  n
bool vis[N];
unordered_map<int,int> mp;
void dfs(int u){
    if(u==2*n+1){
        int sum=0;
        for(int i=1;i<=n;i++) sum+=abs(tmp[2*i-1]-tmp[2*i]);
        res=max(res,sum);
        mp[sum]++;
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
    freopen("wo.in","r",stdin);
    freopen("wo.out","w",stdout);
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        if(n<=4){
            mp.clear();
            res=-2e18;
            memset(vis,0,sizeof(vis));
            for(int i=1;i<=2*n;i++){
                cin>>a[i];
                if(a[i]) vis[a[i]]=1;
            }
            dfs(1);
            cout<<mp[res]<<"\n";
            continue;
        }
        for(int i=1;i<=2*n;i++){
            cin>>a[i];
            if(!a[i]) continue;
            // if(a[i]<=n) cnt1--;
            // if(a[i]>n) cnt2--;
        }
        int cnt1=n,cnt2=n;
        for(int i=1;i<=2*n;i++){
            if(!a[i]) continue;
            if(a[i]<=n) cnt1--;
            if(a[i]>n) cnt2--;
        }
        // cout<<cnt1<<' '<<cnt2<<endl;
        int res=1;
        for(int i=1;i<=n;i++){
            if(a[2*i-1]&&a[2*i]) continue;
            else if(a[2*i-1]){
                if(a[2*i-1]<=n){
                    if(cnt2) res=(res*cnt2)%mod,cnt2--;
                    else res=(res*cnt1)%mod,cnt1--;
                }
                else{
                    if(cnt1) res=(res*cnt1)%mod,cnt1--;
                    else res=(res*cnt2)%mod,cnt2--;
                }
            }
            else if(a[2*i]){
                if(a[2*i]<=n){
                    if(cnt2) res=(res*cnt2)%mod,cnt2--;
                    else res=(res*cnt1)%mod,cnt1--;
                }
                else{
                    if(cnt1) res=(res*cnt1)%mod,cnt1--;
                    else res=(res*cnt2)%mod,cnt2--;
                }
            }
            else{
                if(cnt1&&cnt2) res=(res*(cnt1*cnt2)%mod*2)%mod,cnt1--,cnt2--;
                else if(cnt1>=2) res=(res*(cnt1*(cnt1-1)%mod)%mod)%mod,cnt1-=2;
                else if(cnt2>=2) res=(res*(cnt2*(cnt2-1)%mod)%mod)%mod,cnt2-=2;
            }
        }
        cout<<res<<"\n";
    }
}