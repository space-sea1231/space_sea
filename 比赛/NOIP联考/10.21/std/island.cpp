#include <bits/stdc++.h>
using namespace std;
const int N=3000010;
const int dx[4]={-1,0,0,1},dy[4]={0,-1,1,0};
int n,m,q,mx=0,my=0;
vector<char> s[N];
vector<int> dis[N];
vector<int> g[N];
char st[N];
struct ege {
    int u, v, w;
} eg[N];
int tot=0;
int fa[N], nd[N];
int ndc=0;
int val[N];
int cg(int x, int y, int id) {
    return id * n * m + (x-1) * m + y;
}
void add(int p, int q, int r) {
    eg[++tot] = { p, q, r };
}
bool cmp(ege x, ege y) {
    return x.w > y.w;
}
int gf(int x) {
    return x == fa[x] ? x : fa[x] = gf(fa[x]);
}
int dep[N],anc[N][20];
void dfs(int x, int fat) {
    dep[x] = dep[fat] + 1;
    anc[x][0] = fat;
    for(int i = 1; i < 20; ++ i){
        anc[x][i] = anc[anc[x][i-1]][i-1];
    }
    for(int i : g[x]){
        dfs(i, x);
    }
}
int lca(int x, int y) {
    if(dep[x] > dep[y]){
        swap(x, y);
    }
    for(int i = 19; i >= 0; -- i){
        if(dep[anc[y][i]] >= dep[x]){
            y = anc[y][i];
        }
    }
    if(x == y){
        return y;
    }
    for(int i = 19; i >= 0; -- i){
        if(anc[x][i] != anc[y][i]){
            x = anc[x][i];
            y = anc[y][i];
        }
    }
    return anc[x][0];
}
int main() {
    freopen("island.in","r",stdin);
    freopen("island.out","w",stdout);
    scanf("%d%d%d", &n, &m, &q);
    queue<pair<int, int> > qu;
    for(int i = 1; i <= n; ++ i){
        s[i].resize(m+1);
        dis[i].resize(m+1);
        scanf("%s", st + 1);
        for(int j = 1; j <= m; ++ j){
            s[i][j] = st[j];
            dis[i][j] = -1;
            if(s[i][j] == 'v'){
                qu.push(make_pair(i, j));
                dis[i][j] = 0;
            } else if(s[i][j] == '#'){
                if(i > mx){
                    mx = i;
                    my = j;
                }
            }
        }
    }
    while(!qu.empty()){
        int x = qu.front().first;
        int y = qu.front().second;
        qu.pop();
        for(int i = 0; i < 4; ++ i){
            int xx = x + dx[i], yy = y + dy[i];
            if(xx >= 1 && xx <= n && yy >= 1 && yy <= m && dis[xx][yy] == -1){
                dis[xx][yy] = dis[x][y] + 1;
                qu.push(make_pair(xx, yy));
            }
        }
    }
    for(int i = 1; i <= n; ++ i){
        for(int j = 1; j <= m; ++ j){
            fa[cg(i, j, 0)] = nd[cg(i, j, 0)] = cg(i, j, 0);
            fa[cg(i, j, 1)] = nd[cg(i, j, 1)] = cg(i, j, 1);
            if(s[i][j] == '#'){
                continue;
            }
            for(int k = 2; k < 4; ++ k){
                int x = i + dx[k], y = j + dy[k];
                if(x >= 1 && x <= n && y >= 1 && y <= m && s[x][y] != '#'){
                    if(j == y && j > my && min(i, x) == mx){
                        add(cg(i, j, 0), cg(x, y, 1), min(dis[i][j], dis[x][y]));
                        add(cg(i, j, 1), cg(x, y, 0), min(dis[i][j], dis[x][y]));
                    } else {
                        add(cg(i, j, 0), cg(x, y, 0), min(dis[i][j], dis[x][y]));
                        add(cg(i, j, 1), cg(x, y, 1), min(dis[i][j], dis[x][y]));
                    }
                }
            }
        }
    }
    ndc = cg(n, m, 1);
    sort(eg + 1, eg + tot + 1, cmp);
    for(int i = 1; i <= tot; ++ i){
        int u = eg[i].u, v = eg[i].v, w = eg[i].w;
        if(gf(u) == gf(v)){
            continue;
        }
        u = gf(u), v = gf(v);
        fa[u] = v;
        ++ ndc;
        g[ndc].push_back(nd[u]);
        g[ndc].push_back(nd[v]);
        nd[v] = ndc;
        val[ndc] = w;
    }
    dfs(ndc, 0);
    
    while(q--){
        int x, y;
        scanf("%d%d", &x, &y);
        int st = cg(x, y, 0), ed = cg(x, y, 1);
        printf("%d\n", val[lca(st, ed)]);
    }
    return 0;
}