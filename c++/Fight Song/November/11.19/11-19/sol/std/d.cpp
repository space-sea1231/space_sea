#include<bits/stdc++.h>
using namespace std;using ll=__int128;
using P=pair<ll,ll>;using Pi=pair<ll,P>;using Pp=pair<P,ll>;
long long tmp;
#define read(x) (cin>>tmp,x=tmp)
#define write(x) (tmp=x,cout<<tmp)
const ll N=1e5+2;ll n,m;P ans[N];bool vis[N];vector<Pi> v[N];
inline P operator +(const P a,const P b){return P{a.first+b.first,a.second+b.second};}
#define add(x) (((__int128)A)*((x).first)+((__int128)B)*((x).second))
inline void dijkstra(ll A,ll B){
	for(int i=1;i<=n;i++)ans[i]=P{1e18,1e18},vis[i]=0;
	priority_queue<P,vector<P>,greater<P> > pq;
	ans[1]=P{0,0};pq.emplace(P{0,1});
	while(!pq.empty()){
		ll x=pq.top().second;pq.pop();
		if(vis[x])continue;
		vis[x]=1;
		for(Pi t:v[x])if(add(ans[t.first])>add(ans[x]+t.second)
		||(add(ans[t.first])==add(ans[x]+t.second)&&ans[t.first]>ans[x]+t.second))
			ans[t.first]=ans[x]+t.second,pq.emplace(P{add(ans[t.first]),t.first});
	}
}
inline Pi solve(P a,P b){
	if(a==b)return Pi{1e18,P{0,0}};
	ll A=a.second-b.second,B=b.first-a.first;
	dijkstra(A,B);P now=ans[n];
	if(add(now)>=A*a.first+B*a.second)return Pi{1e18,P{0,0}};
	return min(min(solve(a,now),solve(now,b)),Pi{now.first*now.second,now});
}
int main(){
	freopen("d.in","r",stdin),freopen("d.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int T;cin>>T;
	while(T--){
		read(n),read(m);
		for(int i=1;i<=n;i++)v[i].clear();
		while(m--){ll x,y,a,b;read(x),read(y),read(a),read(b),v[x].emplace_back(Pi{y,P{a,b}});}
		dijkstra(1,0);P a=ans[n];dijkstra(0,1);P b=ans[n];
		Pi ans=min(min(Pi{a.first*a.second,a},Pi{b.first*b.second,b}),solve(a,b));
		write(ans.second.first),cout<<" ",write(ans.second.second),cout<<"\n";
	}
	return 0;
}
