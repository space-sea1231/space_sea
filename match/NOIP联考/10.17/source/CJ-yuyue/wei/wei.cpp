#include <bits/stdc++.h>
using namespace std;
namespace fisher{
#define int long long
#define per(i,a,b) for(int i=(a);i<=(b);i++)
#define rep(i,b,a) for(int i=(b);i>=(a);i--)
const int N=4e5+5,mod=(1ll<<32);
int T,n,ans,p[N];
bool check(int l,int r){
	per(i,l+1,r) if(p[i-1]>=p[i]) return 0;
	return 1;
}
int calc(){
	int res=0;
	per(i,1,n) per(j,i,n)
		res+=check(i,j);
	return res;
}
void main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	freopen("wei.in","r",stdin);
	freopen("wei.out","w",stdout);
	for(cin>>T;T--;){
		cin>>n;
		per(i,1,n) cin>>p[i];
		ans=calc();
		per(i,1,n) per(j,i+1,n){
			swap(p[i],p[j]);
			ans=max(ans,calc());
			swap(p[i],p[j]);
		}
		cout<<ans<<'\n';
	}
}}
signed main(){
	fisher::main();
	return 0;
}
