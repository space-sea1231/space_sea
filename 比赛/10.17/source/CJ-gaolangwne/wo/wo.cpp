#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e6+5;
const int mod=998244353;
int T,n;
int p[N];
int jc[N];
int vis[N];
vector<int> a;
int us;
int once;
int cc;
int twice;
int ksm(int x,int y){
    int base=x;
    int ans=1;
    while(y){
        if(y&1)ans*=base;
        base*=base;
        base%=mod;
        ans%=mod;
        y/=2;
    }
    return ans;
}
signed main(){
    freopen("wo.in","r",stdin);
    freopen("wo.out","w",stdout);
    cin >> T;
    while(T--){
        cin >> n;
        us=n;
        once=cc=twice=0;
        jc[0]=1;
        jc[1]=1;
        for(int i=2;i<=n*2;i++){
            jc[i]=jc[i-1]*i;
            jc[i]%=mod;
        }
        for(int i=1;i<=n*2;i++){
            cin >> p[i];    
        }
        a.clear();
        for(int i=1;i<=n;i++){
            if(p[i*2]>0&&p[i*2-1]>0){
                us--;
                vis[p[i*2]]=1;
                vis[p[i*2-1]]=1;
            }
        }
        for(int i=1;i<=n*2;i++)if(!vis[i])a.push_back(i);
        sort(a.begin(),a.end());
        int mid=a.size()/2 - 1;
        int midd=a[mid];
        for(int i=1;i<=n;i++){
            if(p[i*2]>0&&p[i*2-1]>0){
                continue;
            }else if((p[i*2]>0||p[i*2-1]>0)&&max(p[i*2],p[i*2-1])<=midd){
                once++;
                cc++;
            }else if(p[i*2]>0||p[i*2-1]>0){
                twice++;
                cc++;
            }
        }
        int ans=1;
        ans*=jc[us-once];
        ans*=jc[us-twice];
        ans%=mod;
        ans*=ksm(2,us-cc);
        ans%=mod;
        cout << ans << "\n";
    }
}
