#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int t, n, m, cnt;
int head[N], to[N<<1], nxt[N<<1];
int ru[N], sum[N];
bool vis[N];
void init(){
    memset(head, 0, sizeof(head));
    memset(to, 0, sizeof(to));
    memset(nxt, 0, sizeof(nxt));
    memset(ru, 0, sizeof(ru));
    memset(vis, 0, sizeof(vis));
    memset(sum, 0, sizeof(sum));
    cnt=0;
}
void add(int u, int v){
    to[++cnt]=v;
    nxt[cnt]=head[u];
    head[u]=cnt;
}
bool Topu(){
    priority_queue<int> q;
    int num=0, top=0;
    for (int i=1; i<=n; i++){
        if (ru[i]==0){
            q.push(i);
            vis[i]=1;
            num++;
        }
    }
    while (!q.empty()){
        int u=q.top();
        q.pop();
        sum[++top]=u;
        for (int i=head[u]; i; i=nxt[i]){
            int v=to[i];
            if (!vis[v]){
                ru[v]--;
                if (ru[v]==0){
                    q.push(v);
                    vis[v]=1;
                    num++;
                }
            }
        }
    }
    return num==n;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> t;
    while (t--){
        init();
        cin >> n >> m;
        for (int i=1; i<=m; i++){
            int u, v;
            cin >> u >> v;
            add(v, u);
            ru[u]++;
        }
        if (Topu()){
            for (int i=n; i>=1; i--){
                printf("%d ", sum[i]);
            }
            printf("\n");
        }else{
            printf("Impossible!\n");
            continue;
        }
    }

    return 0;
}