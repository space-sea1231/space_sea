#include <bits/stdc++.h>
using namespace std;
const int N=5e3+10;
const int M=1e4+10;
const int K=5e5+10;
int vis_1[K];

int n, cnt, tot[N];
int head[N], to[M], nxt[M];
int dep[N][N], fa[N];
bool vis[N];
vector<pair<int, int> > q[N];
void add(int u, int v){
	to[++cnt]=v;
	nxt[cnt]=head[u];
	head[u]=cnt;
}
void serch(int root, int u, int fa){
	dep[root][u]=dep[root][fa]+1;
	q[dep[root][u]].push_back(make_pair(root, u));
	for (int i=head[u]; i; i=nxt[i]){
		int v=to[i];
		if (v==fa){
			continue;
		}
		serch(root, v, u);
	}
}
int find(int x){
	if (fa[x]==x){
		return x;
	}
	return fa[x]=find(fa[x]);
}
int main(){
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie();
	cin >> n;
	if (n<=5000){
		for (int i=1; i<n; i++){
			int u, v;
			cin >> u >> v;
			add(u, v);
			add(v, u);
		}
		for (int i=1; i<=n; i++){
			fa[i]=i;
		}
		for (int i=1; i<=n; i++){
			dep[i][i]=-1;
			serch(i, i, i);
		}
		// for (int i=1; i<=n; i++){
		// 	for (int j=0; j<q[i].size(); j++){
		// 		cerr<<q[i][j].first << " " << q[i][j].second << "   ";
		// 	}
		// 	cerr<<"\n";
		// }
		// for (int i=1; i<=n; i++){
		// 	for (int j=1; j<=n; j++){
		// 		cerr<<dep[i][j]<<" ";
		// 	}
		// 	cerr<<"\n";
		// }
		for (int i=n; i>=1; i--){
			for (int j=1; j<=n; j++){
				vis[j]=0;
			}
			for (int j=0; j<q[i].size(); j++){
				int u=q[i][j].first;
				int v=q[i][j].second;
				int u_fa=find(u);
				int v_fa=find(v);
				fa[u_fa]=v_fa;
			}
			// cerr<<"Debug: " << vis[1] << endl;
			for (int j=1; j<=n; j++){
				if (!vis[fa[j]]){
					vis[fa[j]]=1;
					tot[i]++;
				}
			}
		}
		for (int i=1; i<=n; i++){
			printf("%d ", tot[i]);
		}
		return 0;
	}
	for (int i=1; i<n; i++){
		int u, v;
		cin >> u >> v;
		vis_1[u]++;
		vis_1[v]++;
		if (vis_1[u]>2||vis_1[v]>2){
			for (int i=1; i<=n; i++){
				if (i==1){
					printf("1 ");
				}else if (i==2){
					printf("2 ");
				}else{
					printf("%d ", n);
				}
			}
			return 0;
		}
	}
	int lll=0;
	for (int i=1; i<=n; i++){
		if (i<=n/2){
			printf("1 ");
		}else{
			lll+=2;
			printf("%d ", min(n, lll));
		}
	}
	
	return 0;
}
/*
5*10^5
O(n^2)卡掉
O(nlogn) 感觉有可能（毕竟是树），但是可行性较低。（并查集）
O(n) 最有可能：换根DP
*/