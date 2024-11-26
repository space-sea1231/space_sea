#include<bits/stdc++.h>
using namespace std;
#define rint register int
#define ll long long
#define rll register long long

int T,n,p[400005];
ll ans;
int main(){
    freopen("wei.in","r",stdin);
    freopen("wei.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n,ans=0;
        for(rint i=1;i<=n;i++)cin>>p[i];
        for(rint i=1;i<=n;i++){
            for(rint j=i+1;j<=n;j++){
                rll res=0,sum=0;
                swap(p[i],p[j]);
                for(rint x=1;x<=n;x++){
                    if(p[x]>p[x-1])sum++;
                    else{
                        res+=sum*(sum+1)/2;
                        sum=1;
                    }
                }
                res+=sum*(sum+1)/2;
                swap(p[i],p[j]);
                ans=max(ans,res);
            }
        }
        cout<<(unsigned int)ans<<"\n";
    }
    return 0;
}