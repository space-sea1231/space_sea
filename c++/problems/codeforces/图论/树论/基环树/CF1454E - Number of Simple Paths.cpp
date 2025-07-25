#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int t, n, cnt, ans, top_loop, top;
int head[N], nxt[N<<1], to[N<<1];
int stk[N], loop[N];
bool vis[N], vis_loop[N], flag;
void init(){
    memset(vis, 0, sizeof(vis));
    memset(vis_loop, 0, sizeof(vis_loop));
    memset(head, 0, sizeof(head));
    top=1, top_loop=0;
    cnt=0, flag=0;
}
void add(int u, int v){
    to[++cnt]=v;
    nxt[cnt]=head[u];
    head[u]=cnt;
}
void search(int u, int fa){
    stk[++top]=u;
    vis[u]=1;
    for (int i=head[u]; i; i=nxt[i]){
        int v=to[i];
        if (v==fa){
            continue;
        }
        if (!vis[v]){
            search(v, u);
        }else{
            while (stk[top]!=v){
                loop[++top_loop]=stk[top];
                vis_loop[stk[top]]=1;
                top--;
            }
            loop[++top_loop]=v;
            vis_loop[v]=1;
            flag=1;
        }
        if (flag){
            return ;
        }
    }
    top--;
}
int dfs(int u, int fa){
    int cnt=1;
    for (int i=head[u]; i; i=nxt[i]){
        int v=to[i];
        if (v==fa||vis_loop[v]){
            continue;
        }
        cnt+=dfs(v, u);
    }
    return cnt;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> t;
    while (t--){
        init();
        cin >> n;
        ans=n*(n-1);
        for (int i=1; i<=n; i++){
            int u, v;
            cin >> u >> v;
            add(u, v);
            add(v, u);
        }
        search(1, 0);
        for (int i=1; i<=top_loop; i++){
            int u=loop[i];
            int tmp=dfs(u, 0);
            ans-=tmp*(tmp-1)/2;
        }
        printf("%lld\n", ans);
    }

    return 0;
}