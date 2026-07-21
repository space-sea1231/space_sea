#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int N=200010,M=2000010,inv6=166374059,mod=998244353;
int T,n;
ll sum,tmp;
void solve(){
	cin>>n,sum=tmp=0;
	for(int i=1,x;i<=n;i++){
		cin>>x,sum+=x;
		if(i==1)tmp+=x;
		if(i==n)tmp+=x;
	}
	sum%=mod,tmp%=mod,sum=1ll*(n+3)*sum%mod;
	cout<<1ll*(sum+tmp)*inv6%mod<<'\n';
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--)solve();
	return 0;
}
