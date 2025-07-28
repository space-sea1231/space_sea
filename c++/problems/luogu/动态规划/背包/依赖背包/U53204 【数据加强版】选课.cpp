#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

const int N=3e2+10;

int n, m;
int cnt, root;
int weight[N];
int f[N][N];
int head[N], to[N], nxt[N];

void Add(int u, int v){
    to[++cnt]=v;
    nxt[cnt]=head[u];
    head[u]=cnt;
}
void Dfs(int u){
    for (int i=1; i<=m; i++){
        f[u][i]=weight[u];
    }
    for (int i=head[u]; i; i=nxt[i]){
        int v=to[i];
        Dfs(v);
        for (int j=m; j>=1; j--){
            for (int k=0; k<=j-1; k++){
                f[u][j]=max(f[u][j], f[u][j-k]+f[v][k]);
            }
        }
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    m++;
    for (int i=1; i<=n; i++){
        int p;
        cin >> p >> weight[i];
        Add(p, i);
    }
    Dfs(0);
    printf("%d\n", f[0][m]);

    return 0;
}