#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

const int INF=0x3f3f3f3f;

int n;

namespace Pts1{
    const int N=3e3+10;

    int m;
    int cnt;
    int head[N], to[N<<1], nxt[N<<1];
    int dep[N][N];
    int node[N], ans[N];

    void Add(int u, int v){
        to[++cnt]=v;
        nxt[cnt]=head[u];
        head[u]=cnt;
    }
    void Dfs(int u, int fa, int root){
        for (int i=head[u]; i; i=nxt[i]){
            int v=to[i];
            if (v==fa) continue;
            dep[root][v]=dep[root][u]+1;
            Dfs(v, u, root);
        }
    }
}
namespace Pts2{
    const int N=3e5+10;
    const int M=1e6+10;

    int m;
    int cnt, root, num;
    int ru[N], id[N], ans[N];
    int head[N], to[N<<1], nxt[N<<1];

    void Add(int u, int v){
        to[++cnt]=v;
        nxt[cnt]=head[u];
        head[u]=cnt;
    }
    void Dfs(int u, int fa){
        id[u]=++num;
        for (int i=head[u]; i; i=nxt[i]){
            int v=to[i];
            if (v==fa) continue;
            Dfs(v, u);
        }
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n;
    if (n<=3000){
        using namespace Pts1;
        for (int i=2; i<=n; i++){
            int u;
            cin >> u;
            Add(u, i);
            Add(i, u);
        }
        cin >> m;
        for (int i=1; i<=n; i++){
            Dfs(i, 0, i);
            ans[i]=INF;
        }
        for (int i=1; i<=m; i++){
            int k;
            cin >> k;
            for (int j=1; j<=k; j++){
                cin >> node[j];
            }
            for (int j=1; j<=n; j++){
                int maxn=0;
                for (int l=1; l<=k; l++){
                    maxn=max(maxn, dep[j][node[l]]);
                }
                ans[j]=min(ans[j], maxn);
            }
        }
        for (int i=1; i<=n; i++){
            printf("%d\n", ans[i]);
        }
    }
    else{
        using namespace Pts2;
        for (int i=2; i<=n; i++){
            int u;
            cin >> u;
            Add(u, i);
            Add(i, u);
            ru[i]++;
            ru[u]++;
        }
        for (int i=1; i<=n; i++){
            ans[i]=INF;
        }
        cin >> m;
        for (int i=1; i<=n; i++){
            if (ru[i]==1){
                root=i;
                break;
            }
        }
        Dfs(root, 0);
        for (int i=1; i<=m; i++){
            int k;
            cin >> k;
            int minn=INF, maxn=0;
            for (int j=1; j<=k; j++){
                int x;
                cin >> x;
                minn=min(minn, id[x]);
                maxn=max(maxn, id[x]);
            }
            for (int j=1; j<=n; j++){
                ans[j]=min(ans[j], max(minn, maxn));
            }
        }
        for (int i=1; i<=n; i++){
            printf("%d\n", ans[i]);
        }
    }
    return 0;
}