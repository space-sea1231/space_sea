#include <bits/stdc++.h>
using namespace std;
const int N=1<<19;
const int M=1e5+10;
const int INF=1e9+10;
vector<pair<int, int> > q[N];
int n, m, dp[M];
void add(int x, int v, int w){
	int siz=q[x/2].size(), v_fa, w_fa;
	for (int i=0; i<siz; i++){
		v_fa=q[x/2][i].first;
		w_fa=q[x/2][i].second;
		q[x].push_back(make_pair(v_fa, w_fa));
	}
	q[x].push_back(make_pair(v, w));
}
int main(){
    // freopen("hclo.in", "r", stdin);
    // freopen("hclo.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	int v, w;
	for (int i=1; i<=n; i++){
		cin >> v >> w;
		add(i, v, w);
	}
	cin >> m;
	int siz;
	for (int i=1; i<=m; i++){
		// cerr<<i<<endl;
		cin >> v >> w;
		for (int j=0; j<=w; j++){
			dp[j]=0;
		}
		siz=q[v].size();
		for (int j=0; j<siz; j++){
			for (int k=w; k>=q[v][j].second; k--){
				dp[k]=max(dp[k], dp[k-q[v][j].second]+q[v][j].first);
			}
		}
		printf("%d\n", dp[w]);
	}
	return 0;
}