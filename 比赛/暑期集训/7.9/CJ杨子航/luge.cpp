#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

const int N=5e3+10;
const int MOD=998244353;
const int EXP=(MOD+1)>>1;

int n, m;
int cnt;
int a[N];
int f[N][N];
int head[N], to[N<<1], nxt[N<<1];

void Add(int u, int v){
    to[++cnt]=v;
    nxt[cnt]=head[u];
    head[u]=cnt;
}
void Dfs(int u, int fa){
    for (int i=head[u]; i; i=nxt[i]){
        int v=to[i];
        if (v==fa) continue;
        for (int j=0; j<=m-a[v]; j++){
            f[v][j+a[v]]=f[u][j];
        }
        Dfs(v, u);
        for (int j=0; j<=m; j++){
            f[u][j]=(ll)(f[u][j]+f[v][j])*EXP%MOD;
        }
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i=1; i<=n; i++){
        cin >> a[i];
    }
    for (int i=1; i<=n; i++){
        int u, v;
        cin >> u >> v;
        Add(u, v);
        Add(v, u);
    }
    f[1][a[1]]=1;
    Dfs(1, 0);
    printf("%d\n", f[1][m]);

    return 0;
}