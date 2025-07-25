#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=50;
const int M=6e2+10;
const int INF=1LL<<60;
int n, m, ans=INF;
bool vis[N];
vector<int> q[M];
map<int, int> mp;
void paint(int x){
	vis[x]=!vis[x];
	for (int i=0; i<q[x].size(); i++){
		int v=q[x][i];
		vis[v]=!vis[v];
	}
}
void serch_1(int u, int w){
	if (u==(n>>1)+1){
		int st=0;
		for (int i=1; i<=n; i++){
			st^=(1LL<<(i-1))*(!vis[i]);
		}
		if (mp.find(st)!=mp.end()){
			mp[st]=min(mp[st], w);
		}else{
			mp[st]=w;
		}
		return ;
	}
	serch_1(u+1, w);
	paint(u);
	serch_1(u+1, w+1);
	paint(u);
}
void serch_2(int u, int w){
	if (u==n+1){
		int st=0;
		for (int i=1; i<=n; i++){
			st^=(1LL<<(i-1))*vis[i];
		}
		if (mp.find(st)!=mp.end()){
			ans=min(ans, mp[st]+w);
		}
		return ;
	}
	serch_2(u+1, w);
	paint(u);
	serch_2(u+1, w+1);
	paint(u);
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie();
	cin >> n >> m;
	for (int i=1; i<=m; i++){
		int u, v;
		cin >> u >> v;
		q[u].push_back(v);
		q[v].push_back(u);
	}
	serch_1(1, 0);
	serch_2((n>>1)+1, 0);
	printf("%lld", ans);

	return 0;
}