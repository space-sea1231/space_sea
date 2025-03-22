struct Least_Common_Ancestors{
    int cnt;
    int head[N], to[M<<1], nxt[M<<1];
    int dep[N], dp[N][K];
    void Add(int u, int v){
        to[++cnt]=v;
        nxt[cnt]=head[u];
        head[u]=cnt;
    }
    void Dfs(int u, int fa){
        for (int i=head[u]; i; i=nxt[i]){
            int v=to[i];
            if (v==fa){
                continue;
            }
            dep[v]=dep[u]+1;
            dp[v][0]=u;
            for (int j=1; j<K; j++){
                dp[v][j]=dp[dp[v][j-1]][j-1];
            }
            Dfs(v, u);
        }
    }
    int lca(int x, int y){
        if (dep[x]<dep[y]){
            swap(x, y);
        }
        for (int i=K-1; i>=0; i--){
            if (dep[dp[x][i]]>=dep[y]){
                x=dp[x][i];
            }
        }
        if (x==y){
            return x;
        }
        for (int i=K-1; i>=0; i--){
            if (dp[x][i]!=dp[y][i]){
                x=dp[x][i], y=dp[y][i];
            }
        }
        return dp[x][0];
    }
    Least_Common_Ancestors(){
        dep[0]=-1;
    }
};