#include <iostream>
#include <stdio.h>
#include <cstring>
// #define __Debug

using namespace std;
typedef long long ll;

const int N=1e5+10;
const int M=1e8+10;

int n, m;
int cnt, ans;
int siz[N];
int f[M];
int head[N], to[N], nxt[N];

void Add(int u, int v){
    to[++cnt]=v;
    nxt[cnt]=head[u];
    head[u]=cnt;
}
void Dfs(int u){
    siz[u]=1;
    f[(u-1)*m+1]=0;
    for (int i=head[u]; i; i=nxt[i]){
        int v=to[i];
        Dfs(v);
        for (int j=min(m, siz[u]+siz[v]); j>=1; j--){
            f[(u-1)*m+j]++;
            for (int k=max(1, j-siz[u]); k<min(j, siz[v]+1); k++){
                f[(u-1)*m+j]=min(f[(u-1)*m+j], f[(u-1)*m+j-k]+f[(v-1)*m+k]);
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
    #ifdef __Debug
        for (int i=1; i<=n; i++){
            for (int j=1; j<=m; j++){
                printf("Debug1: f[%d][%d]=%d\n", i, j, f[i][j]);
            }
        }
    #endif
    ans=f[m];
    for (int i=2; i<=n; i++){
        ans=min(ans, f[i*m]+1);
    }
    printf("%d\n", ans);

    return 0;
}