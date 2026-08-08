#include<bits/stdc++.h>
#define pd push_back
#define all(A) A.begin(),A.end()
#define lb lower_bound
#define ve std::vector
typedef long long ll;
typedef long long ll;
typedef unsigned long long ul;
typedef long double LD;
bool FileIfstream(std::string name){
	std::ifstream f(name.c_str());
	return f.good();
}
namespace Math{
	ll QP(ll x,ll y,ll mod){ll ans=1;for(;y;y>>=1,x=x*x%mod)if(y&1)ans=ans*x%mod;return ans;}
	ll inv(ll x,ll mod){return QP(x,mod-2,mod);}
}
const int N=2e5+10;
const int mod=998244353;
void solve(){
	//don't forget to open long long
	int n;std::cin>>n;
	ve<ll>A(n+1),f(n+1);
	for(int i=1;i<=n;i++)std::cin>>A[i];
	for(int i=2;i<=n;i++)std::cin>>f[i];
	ll S=0;
	for(int i=2;i<=n;i++)S+=A[i];
	if(S!=0)return std::cout<<(S>0?"1":"-1")<<'\n',void();
	ve<ve<int>>v(n+1);
	for(int i=2;i<=n;i++)v[f[i]].pd(i);
	ve<int>dep(n+1);
	auto dfs=[&](int x,int F,auto self)->void{
		dep[x]=dep[F]+(f[x]<x);
		for(auto &y:v[x])self(y,x,self);
	};
	dfs(1,0,dfs);
	ll ans=0;
	for(int i=2;i<=n;i++)ans+=(n-dep[i])*A[i];
	if(ans>0)std::cout<<1<<'\n';
	else if(ans==0)std::cout<<0<<'\n';
	else std::cout<<-1<<'\n';
}
int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);
	int T=1;
	std::cin>>T;
	while(T--)solve();

#ifndef ONLINE_JUDGE
	std::cerr<<std::fixed<<std::setprecision(10)<<1.0*clock()/CLOCKS_PER_SEC<<'\n';
#endif

	return 0;
}
