#include<bits/stdc++.h>
#define int long long
#define mx(a,n) *max_element(a+1,a+n+1)
#define mn(a,n) *min_element(a+1,a+n+1)
using namespace std;
const int N=100010,M=1000010,INF=0x3f3f3f3f;
int T,x,y,n,m,ans,a[N],b[N];
void solve(){
    cin>>x>>y>>n>>m,ans=x*y;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=m;i++)cin>>b[i];
    a[++n]=b[++m]=0;
    for(int u:{mx(a,n),mn(a,n)})
        for(int v:{mx(b,m),mn(b,m)})
            ans=max(ans,(x+u)*(y+v));
    cout<<ans<<'\n';
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>T;
    while(T--)solve();
	return 0;
}
