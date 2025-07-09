#include <iostream>
#include <stdio.h>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

const int N=2e3+10;
// const int M=1e8+10;

int n, m;
int cnt;
int siz[N];
int f[N][N];
int head[N], to[N], nxt[N];

void Add(int u, int v){
    to[++cnt]=v;
    nxt[cnt]=head[u];
    head[u]=cnt;
}
void Dfs(int u){
    siz[u]=1;
    f[u][1]=1;
    for (int i=head[u]; i; i=nxt[i]){
        int v=to[i];
        Dfs(v);
        for (int j=siz[u]+siz[v]; j>=1; j--){
            for (int k=1; k<j; k++){
                f[u][j]=min(f[u][j], f[u][j-k]+f[v][k]);
            }
        }
        siz[u]+=siz[v];
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    memset(f, 0x3f, sizeof(f));
    cin >> n >> m;
    for (int i=1; i<n; i++){
        int u, v;
        cin >> u >> v;
        Add(u, v);
    }
    Dfs(1);
    printf("%d\n", f[1][m]);

    return 0;
}