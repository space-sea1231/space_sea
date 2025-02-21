#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n;
int a[2005];
int dp[2005];
long long mod=1;
signed main(){
	freopen("wei.in","r",stdin);
	freopen("wei.out","w",stdout);
	for(int i=1;i<=32;i++)mod*=2;
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i];
		if(n<=300){
			int ans=1;
			for(int i=1;i<=n;i++){
				for(int j=i+(i!=1);j<=n;j++){
					swap(a[i],a[j]);
					int cnt=1,num=0;
					for(int k=2;k<=n;k++){
						if(a[k]==a[k-1]+1)++cnt;
						else num+=(cnt+1)*cnt/2%mod,num%=mod,cnt=1;
					}
					num+=(cnt+1)*cnt/2%mod,num%=mod;
					ans=max(ans,num),swap(a[i],a[j]);
				}
			}
			cout<<ans<<"\n";continue;
		}
	}
	return 0;
}
/*
2
3
2 1 3
4
2 1 3 4*/

