#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mo=1ll<<32;
int t,n;
int a[400040],l[400040],r[400040];
int calc(){
	int ans=0,len=0;
	for(int i=1;i<=n;i++){
		if(a[i]<a[i-1]){
			ans+=len*(len+1)/2%mo;
			ans%=mo;
			len=0;
		}
		len++;
	}
	ans+=len*(len+1)/2%mo;
	ans%=mo;
	return ans;
}
void solve(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	int ans=calc();
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			swap(a[i],a[j]);
			ans=max(ans,calc());
			swap(a[i],a[j]);
		}
	}
	cout<<ans<<'\n';
}
signed main(){
	freopen("wei.in","r",stdin);
	freopen("wei.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
}