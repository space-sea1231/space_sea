#include<bits/stdc++.h>
#define int int64_t
using namespace std;
int T,n,a[400005],ans;
int calc(){
	int lst=1,ret=0;
	for(int i=2;i<=n;i++)
		if(a[i]<a[i-1])
			ret+=(i-lst)*(i-lst+1)/2,lst=i;
	ret+=(n-lst+1)*(n-lst+2)/2;
	return ret;
}
int32_t main(){
	freopen("wei.in","r",stdin),freopen("wei.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		ans=calc();
		for(int i=1;i<=n;i++)
			for(int j=i+1;j<=n;j++)
				swap(a[i],a[j]),ans=max(ans,calc()),swap(a[i],a[j]);
		cout<<ans<<'\n';
	}
	return 0;
}