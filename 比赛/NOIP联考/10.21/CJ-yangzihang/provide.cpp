#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e2+10;
const int INF=1e18;
int n,m,a[N][N],b[N][N],dis[N][N],maxn,minn=INF;
void serch_y(int x,int y){
    dis[x][y]=max(dis[x-1][y]+b[x][y],dis[x][y-1]+b[x][y]);
    if (x==n&&y==m){
        maxn=max(maxn, dis[x][y]);
        return;
    }
    if (x+1<=n){
        serch_y(x+1,y);
    }
    if (y+1<=m){
        serch_y(x,y+1);
    }
    return;
}
void serch_x(int x,int y){//1 2
    b[x][y]=0;
    if (x==n&&y==1){
        memset(dis,0,sizeof(dis));
        maxn=0;
        serch_y(1,1);
        minn=min(minn, maxn);
    }
    if (x+1<=n){
        serch_x(x+1,y);
    }
    if (y-1>=1){
        serch_x(x,y-1);
    }
    b[x][y]=a[x][y];
    return;
}
signed main(){
    freopen("provide.in", "r", stdin);
    freopen("provide.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    bool flag=1;
    for (int i=1; i<=n; i++){
        for (int j=1; j<=m; j++){
            cin >> a[i][j];
            b[i][j]=a[i][j];
            if (a[i][j]!=1){
                flag=0;
                // printf("Debug1: %lld %lld %lld\n", i, j, a[i][j]);
            }
        }
    }
    if (flag){
        printf("%lld", n+m-3);
        return 0;
    }
    serch_x(1,m);
    printf("%lld", minn);

    return 0;
}