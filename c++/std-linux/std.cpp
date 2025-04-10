#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e6+10;
int n;
ll cnt, ans, sum1, sum2;
ll dep[N], sit[N], sat[N];
int head[N], to[N<<1], nxt[N<<1], val[N<<1];
vector<int> q;
void Add(int u, int v, int w=1){
    to[++cnt]=v;
    val[cnt]=w;
    nxt[cnt]=head[u];
    head[u]=cnt;
}

namespace Pseudotree{
    int num;
    int dfn[N], father[N];
    bool loop[N];
    void Loop(int u, int fa){
        dfn[u]=++num;
        father[u]=fa;
        for (int i=head[u]; i; i=nxt[i]){
            int v=to[i];
            if (v==fa) continue;
            if (dfn[v]){
                if (dfn[v]>dfn[u]){
                    while (v!=u){
                        loop[v]=1;
                        q.push_back(v);
                        v=father[v];
                    }
                    loop[v]=1;
                    q.push_back(v);
                }
            }else{
                Loop(v, u);
            }
        }
    }
}using namespace Pseudotree;

void Dfs(int u, int fa){
    for (int i=head[u]; i; i=nxt[i]){
        int v=to[i], w=val[i];
        if (v==fa||loop[v]) continue;
        Dfs(v, u);
        sum1=max(sum1, dep[u]+dep[v]+w);
        dep[u]=max(dep[u], dep[v]+w);
    }
}
ll Solve(int x){
    sum1=0, sum2=0;
    q.clear();
    Loop(x, 0);
    for (auto u:q){
        Dfs(u, 0);
    }
    ll u=q[0], fa=0, top=0, tot=0, siz=q.size();
    do{
        for (int i=head[u]; i; i=nxt[i]){
            int v=to[i], w=val[i];
            if (siz==2){
                if (loop[v]){
                    sit[++top]=dep[v];
                    sat[top]=w;
                    tot+=w;
                    break;
                }
            }
            if (loop[v]&&v!=fa){
                sit[++top]=dep[v];
                sat[top]=w;
                tot+=w;
                fa=u, u=v;
                break;
            }
        }
        /*Debug5:*/
        // printf("Debug5: %d %d %d\n", u, fa, q[0]);
        // if (++cnt>=500) return 0;
    }while(u!=q[0]);
    sat[1]=0;
    ll max1=0, max2=0, sum=0;
    /*Debug3:Check*/
    // printf("Debug3: %d\n", tot);
    for (int i=1; i<=top; i++){
        /*Debug4:Check*/
        // printf("Debug4: %d %d %d\n", i, sit[i], sat[i]);
        sum+=sat[i];
        sum2=max(sum2, sit[i]+sum+max1);
        sum2=max(sum2, tot+sit[i]-sum+max2);
        max1=max(max1, sit[i]-sum);
        max2=max(max2, sit[i]+sum);
    }
    return max(sum1, sum2);
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int i=1; i<=n; i++){
        int v, w;
        cin >> v >> w;
        Add(i, v, w), Add(v, i, w);
    }
    for (int i=1; i<=n; i++){
        if (!dfn[i]){
            /*Debug2:Check*/
            ll tmp=Solve(i);
            // printf("Debug2: %d %d\n", i, tmp);
            ans+=tmp;
        }
    }
    /*Debug1:Check*/
    // for (int i=1; i<=n; i++){
    //     printf("Debug1: %d %d\n", i, dep[i]);
    // }
    printf("%lld\n", ans);
    
    return 0;
}