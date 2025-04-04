#include <bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int n;
int cnt, tot, ans;
int head[N], to[N<<1], nxt[N<<1], val[N<<1];
void Add(int u, int v, int w=1){
    to[++cnt]=v;
    val[cnt]=w;
    nxt[cnt]=head[u];
    head[u]=cnt;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int i=1; i<=n; i++){
        int u=i, v;
        cin >> v;
        Add(v[i], i);
    }
    for (int i=1; i<=n; i++){
        if (!dfn)
    }
    printf("%d\n", ans);

    return 0;
}