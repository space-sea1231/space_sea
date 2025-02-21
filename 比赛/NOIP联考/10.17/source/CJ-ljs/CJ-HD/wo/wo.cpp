#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
const int M=2e6+5;
int t,n,m,a[M];
int p1[M],p2[M];
int ans;
int cnt1,cnt2;
signed main(){
	freopen("wo.in","r",stdin);
	freopen("wo.out","w",stdout);
	cin>>t;
	p1[0]=p2[0]=1;
	for(int i=1;i<=M-5;i++){
		p1[i]=p1[i-1]*i%mod;
		p2[i]=p2[i-1]*i%mod*2%mod;
	}
	for(int i=1;i<=t;i++){
		scanf("%lld",&n);
		cnt1=cnt2=n;ans=1;
		for(int j=2;j<=n*2+1;j++){
			scanf("%lld",&a[j]);
		}
		for(int j=2;j<=n*2+1;j++){
			if(!a[j])continue;
			if(a[j]&&a[j^1]){
				if((j&1)==0)cnt1--,cnt2--;
				continue;
			}
			else if(a[j]<=n)cnt1--;
			else cnt2--;
		}
		for(int j=2;j<=n*2+1;j++){
			if(a[j]&&(!a[j^1])){
				if(a[j]>n){
					ans=(ans*cnt1)%mod;
					cnt1--;
				}
				else ans=(ans*cnt2)%mod,cnt2--;
			}
		}
//		cout<<cnt1<<" ";
//		if(cnt1!=cnt2)cout<"!!!!!!!!!!!!!\n";
		ans=(ans*p1[cnt1]%mod*p2[cnt1])%mod;
		printf("%lld\n",ans);
	}
	return 0;
}
