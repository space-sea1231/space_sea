#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

const int N=1e3+10;
const int M=1e5+N;

int n, m;
int cnt, root;
int weight[N], siz[N];
int f[M];
int head[N], to[N], nxt[N];

void Add(int u, int v){
    to[++cnt]=v;
    nxt[cnt]=head[u];
    head[u]=cnt;
}
void Dfs(int u){
    siz[u]=1;
    f[u*m+1]=weight[u];
    for (int i=head[u]; i; i=nxt[i]){
        int v=to[i];
        Dfs(v);
        for (int j=min(m, siz[u]+siz[v]); j>=1; j--){
            for (int k=max(1, j-siz[u]); k<=j-1&&k<=siz[v]; k++){
                f[u*m+j]=max(f[u*m+j], f[u*m+j-k]+f[v*m+k]);
            }
        }
        siz[u]+=siz[v];
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
    printf("%d\n", f[m]);

    return 0;
}
//f[i][j]->f[i*m+j]