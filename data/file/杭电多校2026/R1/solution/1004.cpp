#include<bits/stdc++.h>
using namespace std;
#define mk make_pair
#define MID int mid=(l+r)>>1;
#define ll long long
#define endl '\n'
#define siz(a) int(a.size())
int n,tot,fa[200100],vis[200100],f[200100],a[200100],b[200100];
struct node{
	int a,b,u;
};
bool operator<(node a,node b){
	if(1ll*a.a*b.b==1ll*a.b*b.a){
		if(a.u==b.u)return a.a<b.a;
		return a.u<b.u;
	}
	return 1ll*a.a*b.b<1ll*a.b*b.a;
}
int fi(int x){
	if(f[x]==x)return x;
	return f[x]=fi(f[x]);
}
void solve(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		cin>>b[i];
	}
	for(int i=1;i<=n;i++){
		cin>>fa[i];
	}
	priority_queue<node>q;
	for(int i=1;i<=n;i++){
		f[i]=i;
		vis[i]=0;
		q.push(node{a[i],b[i],i});
	}
	ll ans=0;
	while(!q.empty()){
		node tmp=q.top();q.pop();
		int u=tmp.u;
		if(vis[u])continue;
		vis[u]=1;
		if(fa[u]){
			int v=fi(fa[u]);
			ans+=1ll*b[v]*a[u];
			f[u]=v;
			a[v]+=a[u];
			b[v]+=b[u];
			q.push(node{a[v],b[v],v});
		}
	}
	cout<<ans<<endl;
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	int TTT;
	cin>>TTT;
	while(TTT--)solve();
}
