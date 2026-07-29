#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;
typedef long long ll;

const int N=1e5+10;
const int Mod=1e9+7;

int n, m, k;
ll pos[N], a[N], sum[N];
bool vis[N];

void search(int dep){
    if (dep==m+1){
        for (int i=1; i<=m; i++){
            sum[a[i]]=(sum[a[i]]+pos[a[i]])%Mod;
        }
        return ;
    }
    int tmp=pos[a[dep]];
    if (a[dep]>1){
        pos[a[dep]]=-pos[a[dep]]+(pos[a[dep]-1]<<1);
        search(dep+1);
    }
    pos[a[dep]]=tmp;
    if (a[dep]<n){
        pos[a[dep]]=-pos[a[dep]]+(pos[a[dep]+1]<<1);
        search(dep+1);
    }
    pos[a[dep]]=tmp;
}
signed main(){
    freopen("chess.in", "r", stdin);
    freopen("chess.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i=1; i<=n; i++){
        cin >> pos[i];
    }
    cin >> m >> k;
    for (int i=1; i<=m; i++){
        cin >> a[i];
        vis[a[i]]=1;
    }
    search(1);
    for (int i=1; i<=n; i++){
        if (vis[i]){
            printf("%lld ", sum[i]);
        }else{
            printf("%lld ", (1LL<<m)*pos[i]%Mod);
        }
    }
    return 0;
}