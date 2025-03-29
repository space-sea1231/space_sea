#include <bits/stdc++.h>
using namespace std;
const int N=5e5+10;
int start_1, start_2, start_3, start_4;
int n, m, cnt, maxn;
int dep_1[N], dep_2[N], dep_3[N], dep_4[N];
int fa[N], tot[N], edge[N];
int head[N], nxt[N*2], to[N*2];
vector<int> q_1[N], q_2[N], q_3[N], q_4[N];
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
	if (maxn<dep_2[u]&&u!=start_2&&u!=start_1){
		maxn=dep_2[u];
		start_3=u;
	}
	for (int i=head[u]; i; i=nxt[i]){
		int v=to[i];
		if (v==fa){
			continue;
		}
		serch_2(v, u);
	}
}
void serch_3(int u, int fa){
	dep_3[u]=dep_3[fa]+1;
	q_3[dep_3[u]].push_back(u);
	if (maxn<dep_3[u]&&u!=start_2&&u!=start_1&&u!=start_3){
		maxn=dep_3[u];
		start_4=u;
	}
	for (int i=head[u]; i; i=nxt[i]){
		int v=to[i];
		if (v==fa){
			continue;
		}
		serch_3(v, u);
	}
}
void serch_4(int u, int fa){
	dep_4[u]=dep_4[fa]+1;
	q_4[dep_4[u]].push_back(u);
	for (int i=head[u]; i; i=nxt[i]){
		int v=to[i];
		if (v==fa){
			continue;
		}
		serch_4(v, u);
	}
}
int main(){
	// freopen("tree.in", "r", stdin);
	// freopen("tree.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie();
	cin >> n;serch_3(start_3, 0);
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
	dep_1[0]=-1, dep_2[0]=-1, dep_3[0]=-1;
	serch_1(start_1, 0);
	maxn=0;
	serch_2(start_2, 0);
	maxn=0;
	serch_3(start_3, 0);
	serch_4(start_4, 0);
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
		for (int j=0; j<q_3[i].size(); j++){
			int v=q_3[i][j];
			if (fa[v]==0&&v!=start_1){
				fa[v]=start_1;
				tot[i]--;
			}
		}
		for (int j=0; j<q_4[i].size(); j++){
			int v=q_4[i][j];
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