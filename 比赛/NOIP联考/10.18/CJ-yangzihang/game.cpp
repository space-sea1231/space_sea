#include <bits/stdc++.h>
using namespace std;
const int N=4e2+10;
const int INF=1e9;
bool flag, vis[N];
int n, m, cnt, head[N], dep[N], maxn=-INF, minn=INF;
struct node{
    int to, next;
}e[N*2];
void add(int u, int v){
    e[++cnt].to=v;
    e[cnt].next=head[u];
    head[u]=cnt;
}
void serch(int u, int fa){
    dep[u]=dep[fa]+1;
    int v;
    for (int i=head[u]; i; i=e[i].next){
        v=e[i].to;
        if (v==fa){
            continue;
        }
        serch(v, u);
    }
}
void serch_1(int u, int fa, int kkksc03){
    if (vis[u]||flag){
        return;
    }
    if (kkksc03==m){
        printf("Yes");
        flag=1;
        return;
    }
    int vv, v;
    for (int j=head[u]; j; j=e[i].next){
        vv=e[j].to;
        if (vv==fa){
            continue;
        }
        vis[vv]=1;
        for (int i=head[u]; i; i=e[i].next){
            v=e[i].to;
            if (v==fa){
                continue;
            }
            serch_1(v, u, kkksc03+1);
            if (flag){
                return;
            }
        }
        vis[e[j].to]=0;
    }
}
int main(){
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    int u, v;
    for (int i=1; i<n; i++){
        cin >> u >> v;
        add(u, v);
        add(v, u);
    }
    serch(1, 0);
    serch_1(1, 0, 0);
    if (!flag){
        printf("No");
    }
    return 0;
}