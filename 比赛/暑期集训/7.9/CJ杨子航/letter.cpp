#include <iostream>
#include <stdio.h>
#include <vector>
#define __Debug

using namespace std;
typedef long long ll;

const int N=1e5+10;
const int M=5e3+10;

int n, m, q;
int cnt, ans, root;
int head[N], to[N<<1], nxt[N<<1];
int ru[N];

struct Node{
    int x, y;
    bool vis;
}e[N];

void Add(int u, int v){
    to[++cnt]=v;
    nxt[cnt]=head[u];
    head[u]=cnt;
}
bool Check(){
    int cnt=0;
    for (int i=1; i<=n; i++){
        if (ru[i]==1){
            root=i;
            cnt++;
        }
        if (ru[i]>2){
            return false;
        }
    }
    if (cnt==2){
        return true;
    }
    return false;
}

namespace Pts1{
    int top;
    bool flag;
    vector<int> p[M], tmp;
    void Dfs(int u, int fa, int f){
        if (u==f){
            flag=true;
            tmp.push_back(u);
            return;
        }
        for (int i=head[u]; i; i=nxt[i]){
            int v=to[i];
            if (v==fa) continue;
            Dfs(v, u, f);
            if (flag==true){
                tmp.push_back(u);
                return;
            }
        }
    }
}
namespace Pts2{
    int num;
    int id[N];
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

    cin >> n >> m >> q;
    for (int i=1; i<n; i++){
        int u, v;
        cin >> u >> v;
        Add(u, v);
        Add(v, u);
        ru[u]++;
        ru[v]++;
    }
    if (n<=5000&&m<=5000&&q<=5000){
        using namespace Pts1;
        for (int i=1; i<=m; i++){
            int x, y;
            cin >> x >> y;
            e[++top].x=x;
            e[top].y=y;
            p[x].push_back(top);
            p[y].push_back(top);
        }
        for (int i=1; i<=q; i++){
            int opt, x, y;
            cin >> opt >> x >> y;
            switch (opt){
                case 1:
                    tmp.clear();
                    ans=0, flag=false;
                    Dfs(x, 0, y);
                    for (auto &idx:tmp){
                        for (auto &idx1:p[idx]){
                            if (e[idx1].vis==true){
                                ans++;
                            }
                            e[idx1].vis=true;
                        }
                    }
                    for (auto &idx:tmp){
                        for (auto &idx1:p[idx]){
                            e[idx1].vis=false;
                        }
                    }
                    printf("%d\n", ans);
                    break;
                case 2:
                    e[++top].x=x;
                    e[top].y=y;
                    p[x].push_back(top);
                    p[y].push_back(top);
                    break;
            }
        }
        return 0;
    }
    // if (Check()){
    //     using namespace Pts2;
    //     Dfs(root, 0);

    // }
    return 0;
}