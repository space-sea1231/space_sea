#include <bits/stdc++.h>
using namespace std;
const int N=5e3+10;
int n, m, top, uu, vv;
int in[N], sum[N];
bool vis[N], vis_1[N][N];
vector<int> q[N], ans, fina;
void serch(int u, int fa){
	ans.push_back(u);
	for (int i=0; i<q[u].size(); i++){
		int v=q[u][i];
		if (v==fa){
			continue;
		}
		if ((uu==u&&vv==v)||(uu==v&&vv==u)){
			continue;
		}
		serch(v, u);
	}
}
void find(){
 	int l=0, r=0;
    for (int i=1; i<=n; i++){
		if(in[i]==1){
			sum[++r]=i;
			vis[i]=1;
		}
	}
    while(l<r) {
        int u=sum[++l];
        for (int i=0; i<q[u].size(); i++){
            int v=q[u][i];
            if(in[v]>1){
                in[v]--;
                if(in[v]==1){
					sum[++r]=v;
					vis[v]=1;
				}
            }
        }
    }
	for (int i=1; i<=n; i++){
		if (!vis[i]){
			sum[++top]=i;
		}
	}
}
bool pk(vector<int> a, vector<int> b){
	for (int i=0; i<a.size(); i++){
		if (a[i]>b[i]){
			return 1;
		}
		if (a[i]<b[i]){
			return 0;
		}
	}
	return 0;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie();
	cin >> n >> m;
	for (int i=1; i<=m; i++){
		int u, v;
		cin >> u >> v;
		q[u].push_back(v);
		q[v].push_back(u);
		in[u]++, in[v]++;
	}
	for (int i=1; i<=n; i++){
		sort(q[i].begin(), q[i].end());
	}
	if (n==m+1){
		serch(1, 0);
		for (int i=0; i<n; i++){
			printf("%d ", ans[i]);
		}
	}else{
		find();
		for (int i=1; i<=top; i++){
			int u=sum[i];
			for (int j=0; j<q[u].size(); j++){
				int v=q[u][j];
				if (vis_1[u][v]||vis_1[v][u]||vis[v]){
					continue;
				}
				vis_1[u][v]=1;
				vis_1[v][u]=1;
				uu=u, vv=v;
				serch(1, 0);
				if (fina.empty()||pk(fina, ans)){
					fina.clear();
					for (int k=0; k<ans.size(); k++){
						fina.push_back(ans[k]);
					}
				}
				ans.clear();
			}
		}
		for (int i=0; i<fina.size(); i++){
			printf("%d ", fina[i]);
		}
	}
	return 0;
}