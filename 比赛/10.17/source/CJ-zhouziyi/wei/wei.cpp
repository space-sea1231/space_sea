#include<bits/stdc++.h>
#define int long long
#define N 100005
using namespace std;
int T,n,a[N],b[N],res;
signed main(){
    freopen("wei.in","r",stdin);
    freopen("wei.out","w",stdout);
    cin.tie(0)->sync_with_stdio(0);
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i];
        res=0;
        int cnt=0;
        for(int k=1;k<=n;k++){
            int x;
            for(x=k+1;x<=n;x++) if(a[x]<a[x-1]) break;
            cnt+=x-k;
        }
        res=max(res,cnt);
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                for(int k=1;k<=n;k++) b[k]=a[k];
                swap(b[i],b[j]);
                int cnt=0;
                for(int k=1;k<=n;k++){int x;
                    for(x=k+1;x<=n;x++) if(b[x]<b[x-1]) break;
                    cnt+=x-k;
                    // cout<<k<<' '<<x<<endl;
                }
                res=max(res,cnt);
            }
        }
        cout<<res<<"\n";
    }
}