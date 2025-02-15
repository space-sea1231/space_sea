#include<bits/stdc++.h>
using namespace std;
const int N=2e6+114,Mod=998244353;
int t,a[N],s0,s1,n;
long long ans;
long long A(long long z,long long q)
{
	long long res=1;
	for(int i=0;i<q;i++){
		res=res*(z-i)%Mod;
	}
	return res;
}
int main()
{
	freopen("wo.in","r",stdin);
	freopen("wo.out","w",stdout);
	cin>>t;
	while(t--){
		cin>>n;
		ans=1;
		s0=s1=n;
		n*=2;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			if(a[i]==0) continue;
			if(a[i]<=n/2) s0--;
			else s1--;
		}
		for(int i=1;i<=n;i+=2){
			if((a[i]&&a[i+1])||(!(a[i]||a[i+1]))) continue;
			int s=max(a[i],a[i+1]);
			if(s<=n/2){
				ans=ans*s1%Mod;
				s1--;
			}
			else{
				ans=ans*s0%Mod;
				s0--;
			}
		}
//		cout<<s0<<" "<<s1<<endl;
		long long s=min(s0,s1);
		for(int i=0;i<s;i++){
//			cout<<ans<<endl;
			ans=ans*(s0-i)*(s1-i)*2%Mod;
		}
//		cout<<ans<<endl;
		if(s0!=s1){
			ans=ans*A(s0+s1-2*s,s0+s1-2*s)%Mod;
		}
		cout<<ans%Mod<<endl;
	}
    return 0;
}
/*

*/
