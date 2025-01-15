#include<bits/stdc++.h>
using namespace std;
const long long Mod=1ll*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2*2;
int n,a[400010];
long long ans,qz[400010];
long long lx()
{
//	for(int i=1;i<=n;i++){
//		cout<<a[i]<<" ";
//	}
	int res=0,k=1;
	for(int i=2;i<=n;i++){
		if(a[i]>=a[i-1]) k++;
		else{
//			cout<<k<<" ";
			res+=qz[k];
			res%=Mod;
			k=1;
		}
	}
//	cout<<k<<" ";
	res+=qz[k];
//	cout<<res<<endl;
	return res;
}
int main()
{
	freopen("wei.in","r",stdin);
	freopen("wei.out","w",stdout);
	int t;
	cin>>t;
	for(int i=1;i<=100000;i++){
		qz[i]=(qz[i-1]+i)%Mod;
	}
	while(t--)
	{
		ans=0;
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		ans=lx();
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(i==j) continue;
				swap(a[i],a[j]);
				ans=max(ans,lx());
				swap(a[i],a[j]);
			}
		}
		cout<<ans<<endl;
	}
    return 0;
}

