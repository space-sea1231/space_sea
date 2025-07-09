#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

const int N=1e5+10;

int n, m, q;
int cnt, top, ans;
int head[N], to[N<<1], nxt[N<<1];

struct Node{
    int x, y;
    bool vis;
}e[N];

void Add(int u, int v){
    to[++cnt]=v;
    nxt[cnt]=head[u];
    head[u]=cnt;
}
void Dfs(int u, int fa, int f){
    if ()
    for (int i=head[u]; i; i=nxt[i]){
        int v=to[i];
        if (v==fa) continue;

    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> q;
    for (int i=1; i<n; i++){
        int u, v;
        cin >> u >> v;
        Add(u, v);
        Add(v, u);
    }
    if (n<=5000&&m<=5000&&q<=5000){
        for (int i=1; i<=m; i++){
            int x, y;
            cin >> x >> y;
            e[++top].x=x;
            e[top].y=y;
        }
        for (int i=1; i<=q; i++){
            int opt, x, y;
            cin >> opt >> x >> y;
            switch (opt){
                case 1:
                    ans=0;
                    Dfs(x, 0, y);
                    printf("%d\n", ans);
                case 2:
            }
        }
    }
    return 0;
}