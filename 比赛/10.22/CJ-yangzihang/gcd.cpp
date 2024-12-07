#include <bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int n, m;
bool vis[N];
// int find(int x){
    // if (vis[x]==x){
        // return x;
    // }
    // return vis[x]=find(vis[x]);
// }
int gcd(int x, int y){
    int z;
    while (y){
        z=y;
        y=x%y;
        x=z;
    }
    return x;
}
int main(){
    // freopen("gcd.in", "r", stdin);
    // freopen("gcd.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    char c;
    int l, r, x;
    for (int i=1; i<=m; i++){
        cin >>  c;
        if (c=='S'){
            cin >> x;
            if (vis[x]==0){
                vis[x]=1;
                continue;
            }
            vis[x]=0;
        }
        bool flag=0;
        if (c=='C'){
            cin >> l >> r;
            for (int i=l; i<=r; i++){
                if (!vis[i]){
                    continue;
                }
                for (int j=i+1; j<=r; j++){
                    if (!vis[j]){
                        continue;
                    }
                    if (j==i){
                        continue;
                    }
                    if (gcd(i, j)>1){
                        printf("yes\n");
                        flag=1;
                        break;
                    }
                }
                if (flag){
                    break;
                }
            }
            if (!flag){
                printf("no\n");
            }
        }
    }

    return 0;
}