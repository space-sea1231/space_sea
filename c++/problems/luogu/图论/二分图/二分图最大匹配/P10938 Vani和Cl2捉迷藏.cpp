#include <bits/stdc++.h>
using namespace std;
const int N=100000,M=600;
int t, n, m, cnt;
int to[N], nxt[N], head[N],a[M][M];
int match[N];
bool vis[N];
void add(int u, int v){
    to[++cnt]=v;
    nxt[cnt]=head[u];
    head[u]=cnt;
}
bool dfs(int u){
    for (int i=head[u]; i; i=nxt[i]){
        int v=to[i];
        if (!vis[v]){
            vis[v]=1;
            if (!match[v]||dfs(match[v])){
                match[v]=u;
                return 1;
            }
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
        a[u][v]=1;
    }
    for (int k=1; k<=n; k++){
    	for (int i=1; i<=n; i++){
    		for (int j=1; j<=n; j++){
    			a[i][j]|=a[i][k]&a[k][j];
			}
		}    
	}
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)if(a[i][j])add(j+n,i);
    int ans=0;
    for (int i=1; i<=n; i++){
        memset(vis, 0, sizeof(vis));
        if (dfs(i)){
            ans++;
        }
    }
    printf("%d\n", n-ans);
    
    return 0;
}