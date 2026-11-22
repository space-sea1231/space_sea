
#include<bits/stdc++.h>
#define ls(k) k << 1
#define rs(k) k << 1 | 1
#define fi first
#define se second
#define popcnt(x) __builtin_popcount(x)
#define open(s1, s2) freopen(s1, "r", stdin), freopen(s2, "w", stdout);
using namespace std;
typedef __int128 __;
typedef long double lb;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;

const int N = 1e6 + 10, M = 5e3 + 10;
const int W = (M >> 1) + 1;

inline ll read(){
    ll x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
            f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}

inline void write(ll x){
    if(x < 0){
        putchar('-');
        x = -x;
    }
    if(x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}

int n, k;
int dep[N], p[3];
vector<int> E[N];
vector<int> V[2], R[3];

inline bool cmp(int x, int y){
    return R[x].size() < R[y].size();
}

inline void add(int u, int v){
    E[u].push_back(v);
    E[v].push_back(u);
}

inline void dfs(int u, int fa){
    for(auto v : E[u]){
        if(v == fa)
            continue;
        dep[v] = dep[u] + 1;
        dfs(v, u);
    }
}

inline void print(){
    puts("Cerydra~");
    for(int i = 0; i < (n >> 1); ++i){
        write(V[0][i]);
        putchar(' ');
        write(V[1][i]);
        putchar(' ');
    }
    putchar('\n');
}

int siz[M];
pair<int, int> pre[M][M >> 1][2][2];

// 将数量维度改为 bitset 的下标
bitset<W> dp[M][2][2], f[M][2][2];

inline void solve(int u, int fa){
    dp[u][0][0][0] = 1;
    dp[u][1][0][1] = 1;
    siz[u] = 1;

    for(auto v : E[u]){
        if(v == fa)
            continue;

        solve(v, u);

        for(int i = 0; i <= siz[u]; ++i){
            for(int j = 0; j <= siz[v] && i + j <= (n >> 1); ++j){
                for(int x0 = 0; x0 <= 1; ++x0){
                    for(int x1 = 0; x1 <= 1; ++x1){
                        if(!dp[u][x0][x1][i])
                            continue;

                        for(int y0 = 0; y0 <= 1; ++y0){
                            for(int y1 = 0; y1 <= 1; ++y1){
                                if(x0 == y0 && (x1 || y1))
                                    continue;
                                if(!dp[v][y0][y1][j])
                                    continue;

                                f[v][x0][x1 + (x0 == y0)][i + j] = 1;
                                pre[v][i + j][x0][x1 + (x0 == y0)] = {i, x1};
                            }
                        }
                    }
                }
            }
        }

        siz[u] += siz[v];
        siz[u] = min(siz[u], n >> 1);

        // bitset 整块复制
        dp[u][0][0] = f[v][0][0];
        dp[u][0][1] = f[v][0][1];
        dp[u][1][0] = f[v][1][0];
        dp[u][1][1] = f[v][1][1];
    }
}

inline void work(int u, int fa, int num, int op1, int op2){
    V[op1].push_back(u);

    reverse(E[u].begin(), E[u].end());

    for(auto v : E[u]){
        if(v == fa)
            continue;

        int x1 = pre[v][num][op1][op2].se;
        int scnt = num - pre[v][num][op1][op2].fi;
        num = pre[v][num][op1][op2].fi;

        bool flag = 1;
        int x0 = op1;

        for(int y0 = 0; y0 <= 1 && flag; ++y0){
            for(int y1 = 0; y1 <= 1 && flag; ++y1){
                if(x0 == y0 && (x1 || y1))
                    continue;
                if(!dp[v][y0][y1][scnt])
                    continue;

                if(x1 + (x0 == y0) == op2){
                    work(v, u, scnt, y0, y1);
                    flag = 0;
                }
            }
        }

        op1 = x0;
        op2 = x1;
        assert(flag == 0);
    }
}

int main(){
    // freopen("chess.in", "r", stdin);
    // freopen("chess.out", "w", stdout);

    n = read(), k = read();

    for(int u, v, i = 1; i < n; ++i){
        u = read(), v = read();
        add(u, v);
    }

    if(k == 1){
        puts("Neil_Qian AKIOI");
        return 0;
    }

    dfs(1, 1);

    if(k == 2){
        for(int i = 1; i <= n; ++i)
            V[dep[i] & 1].push_back(i);

        if(V[0].size() != V[1].size()){
            puts("Neil_Qian AKIOI");
            return 0;
        }

        print();
        return 0;
    }

    if(k >= 4){
        p[0] = 0, p[1] = 1, p[2] = 2;

        for(int i = 1; i <= n; ++i)
            R[dep[i] % 3].push_back(i);

        sort(p, p + 3, cmp);
        V[0] = R[p[0]], V[1] = R[p[1]];

        for(auto v : R[p[2]]){
            if(V[0].size() < V[1].size())
                V[0].push_back(v);
            else
                V[1].push_back(v);
        }

        print();
        return 0;
    }

    solve(1, 1);

    bool flag =
        dp[1][0][0][n >> 1] |
        dp[1][0][1][n >> 1] |
        dp[1][1][0][n >> 1] |
        dp[1][1][1][n >> 1];
    cerr << pre[2][1][1][1].first << " " << pre[2][1][1][1].second;

    if(!flag){
        puts("Neil_Qian AKIOI");
        return 0;
    }

    for(int i = 0; i < 4; ++i){
        if(dp[1][i & 1][i >> 1][n >> 1]){
            work(1, 1, n >> 1, i & 1, i >> 1);
            break;
        }
    }

    print();
    return 0;
}
