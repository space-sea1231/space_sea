#include<bits/stdc++.h>
using namespace std;
int r,c;
long long a[350][350],f[350][350],g[350][350],dp[350][350][2];
int main() {
    freopen("provide.in","r",stdin);
    freopen("provide.out","w",stdout);
    scanf("%d%d",&r,&c);
    for (int i=1;i<=r;i++) {
        for (int j=1;j<=c;j++) {
            scanf("%lld",&a[i][j]);
        }
    }
    memset(f,0,sizeof(f));
    memset(g,0,sizeof(g));
    f[1][1]=a[1][1];
    for (int j=2;j<=c;j++) f[1][j]=f[1][j-1]+a[1][j];
    for (int i=2;i<=r;i++) {
        f[i][1]=f[i-1][1]+a[i][1];
        for (int j=2;j<=c;j++) {
            f[i][j]=a[i][j]+max(f[i-1][j],f[i][j-1]);
        }
    }
    g[r][c]=a[r][c];
    for (int j=c-1;j>=1;j--) g[r][j]=g[r][j+1]+a[r][j];
    for (int i=r-1;i>=1;i--) {
        g[i][c]=g[i+1][c]+a[i][c];
        for (int j=c-1;j>=1;j--) {
            g[i][j]=a[i][j]+max(g[i+1][j],g[i][j+1]);
        }
    }
    memset(dp,0x3f,sizeof(dp));
    dp[1][c][0]=dp[1][c][1]=0;
    for (int i=1;i<=r;i++) {
        for (int j=c;j>=1;j--) {
            long long curmax=f[i-1][j-1]+g[i][j+1];
            for (int k=j-1;k>=1;k--) {
                curmax=max(curmax,f[i-1][k]+g[i+1][k+1]);
                dp[i][k][1]=min(dp[i][k][1],max(max(dp[i][j][0],curmax),f[i][k-1]+max(g[i+1][k+1],g[i][j+1])));
                curmax=max(curmax,f[i-1][k]+g[i+1][k]);
            }
            curmax=f[i-1][j]+g[i+1][j+1];
            for (int k=i+1;k<=r;k++) {
                curmax=max(curmax,f[k-1][j-1]+g[k][j+1]);
                dp[k][j][0]=min(dp[k][j][0],max(max(dp[i][j][1],curmax),max(f[k-1][j-1],f[i-1][j])+g[k+1][j]));
                curmax=max(curmax,f[k][j-1]+g[k][j+1]);
            }
        }
    }
    printf("%lld\n",min(dp[r][1][0],dp[r][1][1]));
    return 0;
}