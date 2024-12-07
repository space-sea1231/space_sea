#include <bits/stdc++.h>
using namespace std;
namespace fisher{
#define int long long
#define per(i,a,b) for(int i=(a);i<=(b);i++)
#define rep(i,b,a) for(int i=(b);i>=(a);i--)
#define all(x,l,r) &(x)[l],&(x)[r]+1
const int N=1e6+5,mod=998244353;
int T,n,cnt,p[N];
int qpow(int a,int b){
	int res=1;
	for(;b;b>>=1,a=(a*a)%mod)
		if(b&1) res=(res*a)%mod;
	return res;
}
void main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	freopen("wo.in","r",stdin);
	freopen("wo.out","w",stdout);
	for(cin>>T;T--;){
		cin>>n;n<<=1;
		per(i,1,n) cin>>p[i];
		cnt=count(all(p,1,n),0);
		cout<<(cnt?qpow(2,cnt-1):0)<<'\n';
	}
}}
signed main(){
	fisher::main();
	return 0;
}
