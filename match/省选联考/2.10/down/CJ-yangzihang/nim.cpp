#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int cnt, num;
int n, s, a, b;
int head[N], to[N<<1], nxt[N<<1];
int id[N], vis[N<<1];
void Add(int u, int v){
    to[++cnt]=v;
    nxt[cnt]=head[u];
    head[u]=cnt;
}
void GGG(int u, int fa){
    id[u]=++num;
    vis[num]=1;
    for (int i=head[u]; i; i=nxt[i]){
        int v=to[i];
        if (v==fa){
            continue;
        }
        GGG(v, u);
    }
}
int main(){
    freopen("nim.in", "r", stdin);
    freopen("nim.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> s >> a >> b;
    if (b>=a){
        printf("1\n");
        return 0;
    }
    for (int i=1; i<n; i++){
        int u, v;
        cin >> u >> v;
        Add(u, v), Add(v, u);
    }
    for (int i=head[s]; i; i=nxt[s]){
        num=0;
        int ans=0x7fffffff;
        memset(id, 0, sizeof(id));
        memset(vis, 0, sizeof(vis));
        int v=to[i];
        GGG(v, i);
        int now=0, tmp=1;
        while (vis[now+a]){
            now+=a;
            if (tmp*b>=a){
                for (int j=now; j>=now-b*tmp&&j; j--){
                    ans=min(ans, id[j]);
                }
                for (int j=now; j<=num; j++){
                    ans=min(ans, id[j]);
                }
                break;
            }
            for (int j=now; j>=now-b*tmp; j--){
                ans=min(ans, id[j]);
            }
            now+=b;
            tmp++;
        }
        for (int j=now-b*tmp; j<=now+b*tmp&&j; j++){
            ans=min(ans, id[j]);
        }
        printf("%d\n", ans);
    }

    return 0;
}