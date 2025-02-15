#include<bits/stdc++.h>
using namespace std;
#define int long long
#define N 400010
int t,n,a[N],f[N];
signed main(){
    freopen("wei.in","r",stdin);
    freopen("wei.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    srand(time(0));
    cin>>t;
    while(t--){
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>a[i];
            f[i]=0;
        }
        if(n<=300){
            int ans=0;
            for(int i=1;i<=n;i++){
                if(a[i]>a[i-1]){
                    f[i]=f[i-1]+1;
                }
                else{
                    f[i]=1;
                }
                ans+=f[i];
            }
            for(int i=1;i<=n;i++){
                for(int j=i+1;j<=n;j++){
                    swap(a[i],a[j]);
                    int s=0;
                    for(int k=1;k<=n;k++){
                        if(a[k]>a[k-1]){
                            f[k]=f[k-1]+1;
                        }
                        else{
                            f[k]=1;
                        }
                        s+=f[k];
                    }
                    ans=max(ans,s);
                    swap(a[i],a[j]);
                }
            }
            cout<<ans<<endl;
        }
        else{
            int ans=0;
            for(int i=1;i<=n;i++){
                if(a[i]>a[i-1]){
                    f[i]=f[i-1]+1;
                }
                else{
                    f[i]=1;
                }
                ans+=f[i];
            }
            for(int i=1;i<=200;i++){
                int l=(rand()*rand()-rand())%n+1,r=(rand()*rand()-rand())%n+1;
                swap(a[l],a[r]);
                int s=0;
                for(int k=1;k<=n;k++){
                    if(a[k]>a[k-1]){
                        f[k]=f[k-1]+1;
                    }
                    else{
                        f[k]=1;
                    }
                    s+=f[k];
                }
                ans=max(ans,s);
                swap(a[l],a[r]);
            }
            cout<<ans<<endl;
        }
    }
    return 0;
}