#include <bits/stdc++.h>
using namespace std;
const int N=30;
struct node{
    int id, w;
}e[N][N];
int n, m, ans;
int a[N*N], mac[N], cnt[N];
bool vis[N][N<<15];
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> m >> n;
    for (int i=1; i<=n*m; i++){
        cin >> a[i];
    }
    for (int i=1; i<=n; i++){
        for (int j=1; j<=m; j++){
            cin >> e[i][j].id;
        }
    }
    for (int i=1; i<=n; i++){
        for (int j=1; j<=m; j++){
            cin >> e[i][j].w;
        }
    }
    for (int i=1; i<=n*m; i++){
        cnt[a[i]]++;
        int id=e[a[i]][cnt[a[i]]].id;
        int w=e[a[i]][cnt[a[i]]].w;
        int tot=0;
        for (int j=mac[a[i]]+1; ; j++){
            if (vis[id][j]==0){
                tot++;
            }else{
                tot=0;
            }
            if (tot==w){
                for (int k=j-w+1; k<=j; k++){
                    vis[id][k]=1;
                }
                ans=max(ans, j);
                mac[a[i]]=j;
                break;
            }
        }
    }
    printf("%d", ans);

    return 0;
}