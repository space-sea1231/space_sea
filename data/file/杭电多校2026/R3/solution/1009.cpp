#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6+100, mod = 998244353, inv2 = (mod+1) / 2;
int n;
inline int read(){
    char ch = getchar();
    while(!isdigit(ch)) ch = getchar();
    int ans = 0;
    while (isdigit(ch)) ans = ans * 10 + ch - '0', ch = getchar();
    return ans;
}
vector<int> tu[N];
int dep[N];
bool vis[N];
void init(){
    for(int i = 1; i <= n; i++){
        tu[i].clear();
        dep[i] = 0, vis[i] = false;
    }
}
void dfs(int x, int fa, int &len, int &cnt){
    vis[x] = true;
    bool flag = false;
    cnt++;
    for(int p: tu[x]){
        if(p == fa && flag == 0){
            flag = true;
            continue;
        }
        if(vis[p]){
            if(!len) len = dep[x] - dep[p] + 1;
            continue;
        }
        dep[p] = dep[x] + 1, dfs(p, x, len, cnt);
    }
    
}
int solve(){
    int ans = 0;
    for(int i = 1; i <= n; i++){
        if(vis[i]) continue;
        int len = 0, cnt = 0;
        dfs(i, -1, len, cnt);
        ans = (ans + cnt - len) % mod;
        ans = (ans + 1ll * inv2 * len % mod) % mod;
    }
    return ans;
}
int main(){
    int _ = read();
    while(_--){
        init();
        n = read();
        for(int i = 1; i <= n; i++){
            int x = read(), y = read();
            tu[x].push_back(y), tu[y].push_back(x);
        }
        printf("%d\n", solve());
    }
    return 0;
}