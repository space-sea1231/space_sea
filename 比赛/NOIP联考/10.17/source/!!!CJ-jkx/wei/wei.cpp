#include<bits/stdc++.h>
using namespace std;
int T,n,a[1000005];
signed main(){
	freopen("wei.in","r",stdin);
	freopen("wei.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1; i<=n; i++) cin>>a[i];
		unsigned int ans=0;
		for(int i=1; i<=n; i++){
			ans++;
			for(int j=i+1; j<=n; j++){
				if(a[j]<a[j-1]) break;
				ans++;
			}
		}
		for(int I=1; I<=n; I++){
			for(int J=1; J<=n; J++){
				swap(a[I],a[J]);
				unsigned int s=0;
				for(int i=1; i<=n; i++){
					s++;
					for(int j=i+1; j<=n; j++){
						if(a[j]<a[j-1]) break;
						s++;
					}
				}
				ans=max(ans,s);
				swap(a[I],a[J]);
			}
		}
		cout<<ans<<'\n';
	}
	return 0;
}