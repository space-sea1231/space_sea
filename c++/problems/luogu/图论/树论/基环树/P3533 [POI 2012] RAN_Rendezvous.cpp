#include <bits/stdc++.h>
using namespace std;
const int N=5e5+10;
const int K=20;
int n, m;
int cnt, num;
int fa[N], dp[N][K], siz[N];
int top[N], dis[N], dep[N], father[N];
int head[N], to[N<<1], nxt[N<<1];
bool loop[N];
vector<int> q, p;
inline void Add(int u, int v){
    to[++cnt]=v;
    nxt[cnt]=head[u];
    head[u]=cnt;
}
inline int Find(int x){
    if (x==fa[x]){
        return x;
    }
    return fa[x]=Find(fa[x]);
}
void Loop(int u, int fa, int root){
    father[u]=fa;
    for (int i=head[u]; i; i=nxt[i]){
        int v=to[i];
        if (v==root){
            v=u;
            while (v!=root){
                p.push_back(v);
                loop[v]=1;
                v=father[v];
            }
            p.push_back(v);
            loop[v]=1;
            break;
        }else{
            Loop(v, u, root);
        }
    }
}
void Dfs(int u, int fa){
    top[u]=top[fa];
    dep[u]=dep[fa]+1;
    for (int i=head[u]; i; i=nxt[i]){
        int v=to[i];
        if (v==fa||loop[v]) continue;
        dp[v][0]=u;
        for (int i=1; i<K; i++){//dp[5][1]=9 dp[9][1]=7
            dp[v][i]=dp[dp[v][i-1]][i-1];
        }
        Dfs(v, u);
        if (v==5){
            // printf("------------\n");
            // printf("%d %d %d\n", dp[5][1], dp[9][1], dp[5][2]);
        }
    }
}
pair<int, int> Lca(int x, int y){//7 5
    bool flag=0;
    if (dep[x]<dep[y]){
        swap(x, y);
        flag=1;
    }
    int rx=x, ry=y;
    for (int i=K-1; i>=0; i--){
        if (dep[dp[x][i]]>=dep[y]){
            x=dp[x][i];
        }
    }
    // printf("Debug: dep[%d]=%d dep[%d]=%d\n", x, dep[x], y, dep[y]);
    if (x==y){
        int ans=dep[rx]-dep[x];
        if (flag) return make_pair(0, ans);
        return make_pair(ans, 0);
    }
    for (int i=K-1; i>=0; i--){
        if (dp[x][i]!=dp[y][i]){
            x=dp[x][i];
            y=dp[y][i];
        }
    }
    int top=dp[x][0];
    int ans1=dep[rx]-dep[top];
    int ans2=dep[ry]-dep[top];
    if (flag) return make_pair(ans2, ans1);
    return make_pair(ans1, ans2);
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for (int i=1; i<=n; i++){
        fa[i]=top[i]=i;
    }
    for (int i=1; i<=n; i++){
        int u;
        cin >> u;
        if (u!=i){
            Add(u, i);
        }
        int uf=Find(u);
        int vf=Find(i);
        if (uf!=vf){
            fa[vf]=uf;
        }else{
            q.push_back(u);
        }
    }
    for (auto root:q){
        Loop(root, root, root);
        if (!p.empty()){
            int last=0;
            for (auto tp:p){
                dep[tp]=-1;
                Dfs(tp, tp);
                dis[tp]=dis[last]+1;
                last=tp;
            }
            // printf("qpqpqp%d\n",p.size());
            siz[Find(root)]=p.size();
            p.clear();
        }else{
            // dis[root]=-1;
            Dfs(root, root);
            // printf("Debug: %d\n", root);
        }
    }
    for(int i=1;i<=n;i++){
        // for(int j=0;j<3;j++){
        //     printf("dp[%d][%d]=%d\n",i,j,dp[i][j]);
        // }
        // printf("dis[%d]=%d\n",i,dis[i]);
    }
    for (int i=1; i<=m; i++){
        int x, y;
        cin >> x >> y;
        if (Find(x)==Find(y)){
            int disx=dep[x];
            int disy=dep[y];
            int tx=top[x], ty=top[y];
            // printf("top[%d]=%d,top[%d]=%d\n",x,tx,y,ty);    
            if (tx==ty){
                // printf("dep[%d]=%d dep[%d]=%d\n", x, dep[x], y, dep[y]);
                pair<int, int> ans=Lca(x, y);
                printf("%d %d\n", ans.first, ans.second);
                continue;
            }
            int disxx, disyy;
            // printf("Debug: %d %d\n", disx, disy);
            // printf("siz[%d]=%d\n",Find(x),siz[Find(x)]);
            if (dis[tx]<dis[ty]){
                disxx=disx+dis[ty]-dis[tx];
                disyy=disy+siz[Find(y)]-dis[ty]+dis[tx];
            }else{//x=1 dis 2  y=2 dis 1
                disxx=disx+siz[Find(x)]-dis[tx]+dis[ty];
                disyy=disy+dis[tx]-dis[ty];
            }
            // printf("%d dis=%d %d dis=%d\n",x,disxx,y,disyy);
            if (disxx<disyy){
                printf("%d %d\n", disxx, disy);
            }else if (disxx>disyy){
                printf("%d %d\n", disx, disyy);
            }else{
                if (disx>disy){
                    printf("%d %d\n", disxx, disy);
                }else if (disx<disy){
                    printf("%d %d\n", disx, disyy);
                }else{
                    printf("%d %d\n", max(disxx, disy), min(disxx, disy));
                }
            }
        }else{
            printf("-1 -1\n");
        }
    }
    // printf("%d\n", dp[5][2]);
    return 0;
}