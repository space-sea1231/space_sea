#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MOD 1000000007LL
#define T0 5000000
int pri[350005],pc=0;
char vis[T0+1];
int J[T0+1],SJ[T0+1];
ll inv30;
ll pw(ll a,ll e){a%=MOD;if(a<0)a+=MOD;ll r=1;while(e){if(e&1)r=r*a%MOD;a=a*a%MOD;e>>=1;}return r;}
void sieve(){
	J[1]=1;
	for(int i=2;i<=T0;i++){
		if(!vis[i]){
			pri[++pc]=i;
			ll p2=(ll)i*i%MOD,p4=p2*p2%MOD;
			J[i]=(int)((p4-1+MOD)%MOD);
		}
		for(int k=1;k<=pc;k++){
			int p=pri[k];
			ll ip=(ll)i*p;
			if(ip>T0)break;
			vis[ip]=1;
			if(i%p==0){
				ll p2=(ll)p*p%MOD,p4=p2*p2%MOD;
				J[ip]=(int)((ll)J[i]*p4%MOD);
				break;
			}else{
				J[ip]=(int)((ll)J[i]*J[p]%MOD);
			}
		}
	}
	for(int i=1;i<=T0;i++)SJ[i]=(int)(((ll)SJ[i-1]+J[i])%MOD);
}
ll S4(ll x){
	x%=MOD;
	ll x2=x*x%MOD;
	ll t=(3*x2%MOD+3*x%MOD-1+MOD)%MOD;
	ll r=x*(x+1)%MOD*(2*x+1)%MOD*t%MOD;
	return r*inv30%MOD;
}
unordered_map<ll,ll>mp;
ll P(ll x){
	if(x<=0)return 0;
	if(x<=T0)return SJ[(int)x];
	auto it=mp.find(x);
	if(it!=mp.end())return it->second;
	ll ans=S4(x);
	for(ll l=2,r;l<=x;l=r+1){
		ll q=x/l;r=x/q;
		ans=(ans-(r-l+1)%MOD*P(q))%MOD;
	}
	ans%=MOD;if(ans<0)ans+=MOD;
	mp[x]=ans;
	return ans;
}
ll T(ll A,ll B){
	if(A<=0||B<=0)return 0;
	ll L=min(A,B),ans=0;
	for(ll v=1,r;v<=L;v=r+1){
		ll qa=A/v,qb=B/v;
		r=min(min(A/qa,B/qb),L);
		ll s=(P(r)-P(v-1)+MOD)%MOD;
		ans=(ans+s*(qa%MOD)%MOD*(qb%MOD))%MOD;
	}
	return ans;
}
ll pp[21];
int pe[21];
int nf=0;
ll G[21][65];
pair<ll,ll>D[200005];
int nd=0;
void dfs(int i,ll d,ll g){
	if(i>nf){D[++nd]=make_pair(d,g);return;}
	ll cur=d;
	for(int a=0;a<=pe[i];a++){
		dfs(i+1,cur,g*G[i][a]%MOD);
		cur*=pp[i];
	}
}
int main(){
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	inv30=pw(30,MOD-2);
	sieve();
	ll N,M,X;
	cin>>N>>M>>X;
	ll x=X;
	nf=0;
	for(ll p=2;p*p<=x;p+=(p==2?1:2)){
		if(x%p==0){
			int e=0;
			while(x%p==0){x/=p;e++;}
			pp[++nf]=p;
			pe[nf]=e;
		}
	}
	if(x>1){pp[++nf]=x;pe[nf]=1;}
	for(int i=1;i<=nf;i++){
		ll pm=pp[i]%MOD;
		int e=pe[i];
		ll C[65];
		C[0]=1;
		for(int v=1;v<=e;v++){
			ll pv=pw(pm,v),q=pw(pm,2LL*v-1);
			C[v]=q*(((pm+1)%MOD*pv%MOD-1+MOD)%MOD)%MOD;
		}
		ll p4=pw(pm,4);G[i][0]=1;
		for(int v=1;v<=e;v++)G[i][v]=(C[v]-p4*C[v-1]%MOD+MOD)%MOD;
	}
	nd=0;dfs(1,1,1);ll ans=0;
	for(int i=1;i<=nd;i++){
		ll d=D[i].first,g=D[i].second,A=N/d,B=M/d;
		if(A<=0||B<=0)continue;ans=(ans+g*T(A,B))%MOD;
	}
	cout<<ans<<'\n';
	return 0;
}