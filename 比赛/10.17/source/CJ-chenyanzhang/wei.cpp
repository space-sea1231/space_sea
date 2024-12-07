#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=4e5;
const int mod=(1ll<<32);
int t,n,p[N],ans;
void add(){
	int tmp=1,res=0;
	for(int i=2;i<=n+1;i++){
		if(p[i]>p[i-1]) tmp++;
		else{
			res=(res+(tmp*(tmp+1)/2)%mod)%mod;
			tmp=1;
		}
	}
	ans=max(ans,res);
	return;
}
signed main(){
	freopen("wei.in","r",stdin);
	freopen("wei.out","w",stdout);
	cin>>t;
	while(t--){
		cin>>n;
		ans=0;
		for(int i=1;i<=n;i++) cin>>p[i];
		p[n+1]=0;
		add();
		for(int i=1;i<=n;i++){
			for(int j=i+1;j<=n;j++){
				swap(p[i],p[j]);
				add();
				swap(p[i],p[j]);
			}
		}
		cout<<ans<<"\n";
	}
	return 0;
} 
