#include <bits/stdc++.h>
using namespace std;
const int N=5e5+10;
int n, cnt, start_1, maxn, start_2;
int dep_1[N], dep_2[N];
int fa[N], tot[N], edge[N];
int head[N], nxt[N*2], to[N*2];
vector<int> q_1[N], q_2[N];
void add(int u, int v){
	to[++cnt]=v;
	nxt[cnt]=head[u];
	head[u]=cnt;
	edge[u]++;
}
void serch_1(int u, int fa){
	dep_1[u]=dep_1[fa]+1;
	q_1[dep_1[u]].push_back(u);
	if (maxn<dep_1[u]){
		maxn=dep_1[u];
		start_2=u;
	}
	for (int i=head[u]; i; i=nxt[i]){
		int v=to[i];
		if (v==fa){
			continue;
		}
		serch_1(v, u);
	}
}
void serch_2(int u, int fa){
	dep_2[u]=dep_2[fa]+1;
	q_2[dep_2[u]].push_back(u);
	for (int i=head[u]; i; i=nxt[i]){
		int v=to[i];
		if (v==fa){
			continue;
		}
		serch_2(v, u);
	}
}
int main(){
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie();
	cin >> n;
	// for (int i=1; i<=n; i++){
	// 	fa[i]=i;
	// }
	for (int i=1; i<n; i++){
		int u, v;
		cin >> u >> v;
		add(u, v);
		add(v, u);
		// cerr<<"Debug: "<<u<<" "<<v<<endl;
	}
	for (int i=1; i<=n; i++){
		if (edge[i]==1){
			start_1=i;
			break;
		}
	}
	dep_1[0]=-1, dep_2[0]=-1;
	serch_1(start_1, 0);
	serch_2(start_2, 0);
	// cerr<<start_1<<" "<<start_2<<endl;
	// for (int i=1; i<=n; i++){
	// 	for (int j=0; j<q_1[i].size(); j++){
	// 		cerr<<"Debug" << i << ": "<< q_1[i][j]<<" ";
	// 	}
	// 	cerr<<endl;
	// 	// cerr<<"Debug:"<<dep_1[i]<<" "<<dep_2[i]<<endl;
	// }
	// cerr<<endl;
	// for (int i=1; i<=n; i++){
	// 	for (int j=0; j<q_2[i].size(); j++){
	// 		cerr<<"Debug" << i << ": "<< q_2[i][j]<<" ";
	// 	}
	// 	cerr<<endl;
	// 	// cerr<<"Debug:"<<dep_1[i]<<" "<<dep_2[i]<<endl;
	// }
	tot[n+1]=n;
	for (int i=n; i>=1; i--){
		tot[i]=tot[i+1];
		for (int j=0; j<q_1[i].size(); j++){
			int v=q_1[i][j];
			if (fa[v]==0){
				fa[v]=start_1;
				tot[i]--;
			}
		}
		for (int j=0; j<q_2[i].size(); j++){
			int v=q_2[i][j];
			if (fa[v]==0&&v!=start_1){
				fa[v]=start_1;
				tot[i]--;
			}
		}
	}
	for (int i=1; i<=n; i++){
		printf("%d ", tot[i]);
	}

	return 0;
}