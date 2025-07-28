#include<bits/stdc++.h>
// #define int long long
#define pii pair<int,int>
#define db double
using namespace std;
const int N=4e5+5,INF=1e9;
int n,p[N];
long long res,ans;
void sv(){
    cin>>n,ans=0;
    for(int i=1;i<=n;i++)cin>>p[i];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++){
            swap(p[i],p[j]);
            res=0;
            for(int k=1,l;k<n;k++){
                l=k;
                while(k<n&&p[k]<p[k+1])k++;
                res+=(k-l+1)*(k-l+2)/2;
            }ans=max(ans,res);
        }
    printf("%u\n",(unsigned int)ans);
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    freopen("wei.in","r",stdin);
    freopen("wei.out","w",stdout);
    int T=1;cin>>T;while(T--)sv();
    return 0;
}