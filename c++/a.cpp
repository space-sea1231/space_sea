#include <bits/stdc++.h>
using namespace std;
const int N=5e4+10;
const int INF=0x7f7f7f7f;
int n, m;
int cnt, tot, now, top;
int head[N], to[N<<1], nxt[N<<1], val[N<<1];
int dis[N], tmp[N];
bool vis[N];
void Add(int u, int v, int w){
    to[++cnt]=v;
    val[cnt]=w;
    nxt[cnt]=head[u];
    head[u]=cnt;
}
void Dfs(int u, int fa){
    for (int i=head[u]; i; i=nxt[i]){
        int v=to[i];
        if (v!=fa) Dfs(v, u);
    }
    memset(vis, 0, sizeof(vis));
    top=0;
    for (int i=head[u]; i; i=nxt[i]){
        int v=to[i], w=val[i];
        if (v==fa) continue;
        if (dis[v]+w>=now) tot++;
        else tmp[++top]=dis[v]+w;
    }
    sort(tmp+1, tmp+top+1);
    for (int i=1; i<=top; i++){
        if (vis[i]) continue;
        // if (pos<=cnt){
        //     while (vis[pos]&&pos<cnt) pos++;
        //     if (!vis[pos]&&tmp[i]+tmp[pos]>=now){
        //         tot++;
        //         vis[i]=1, vis[pos]=1;
        //     }
        // }
        int pos=lower_bound(tmp+i+1, tmp+top+1, now-tmp[i])-tmp;
        while (vis[pos]) pos++;
        if (pos<=top&&tmp[i]+tmp[pos]>=now){
            tot++;
            vis[i]=1, vis[pos]=1;
        }
    }
    for (int i=top; i>=1; i--){
        if (!vis[i]){
            dis[u]=tmp[i];
            return;
        }
    }
}
bool Check(int mid){
    memset(dis, 0, sizeof(dis));
    now=mid, tot=0;
    Dfs(1, 0);
    return tot>=m;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (int i=1; i<n; i++){
        int u, v, w;
        cin >> u >> v >> w;
        Add(u, v, w), Add(v, u, w);
    }
    int l=1, r=INF, ans=INF;
    while (l<=r){
        int mid=(l+r)>>1;
        if (Check(mid)){
            ans=mid;
            l=mid+1;
        }else{
            r=mid-1;
        }
    }
    printf("%d\n", ans);

    return 0;
}