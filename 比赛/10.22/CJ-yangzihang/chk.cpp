#include <bits/stdc++.h>
using namespace std;
const int N=2e3+10;
int n, m, ru[N], ch[N];
bool vis[N][N];
int main(){
    freopen("chk.in", "r", stdin);
    freopen("chk.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    int u, v;
    for (int i=1; i<=m; i++){
        for (int j=1; j<n; j++){
            cin >> u >> v;
            if (vis[u][v]){//性质1错误
                printf("ERR1");
                return 0;
            }
            vis[u][v]=1;
            ru[v]++;
            ch[u]++;
        }
    }
    for (int i=1; i<=n; i++){
        if (ru[i]==m){
            printf("ERR2\n");
            return 0;
        }
    }
    printf("OK\n");
    
    return 0;
}