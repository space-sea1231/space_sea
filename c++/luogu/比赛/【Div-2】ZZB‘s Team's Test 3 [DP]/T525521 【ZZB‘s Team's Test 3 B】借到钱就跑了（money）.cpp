#include <bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int a[N], b[N], c[N], dp[N][3], n;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i=1; i<=n; i++){
        cin >> a[i] >> b[i] >> c[i];
    }
    for (int i=1; i<=n; i++){
        dp[i][0]=max(dp[i-1][1]+a[i], dp[i-1][2]+a[i]);
        dp[i][1]=max(dp[i-1][0]+b[i], dp[i-1][2]+b[i]);
        dp[i][2]=max(dp[i-1][0]+c[i], dp[i-1][1]+c[i]);
    }
    printf("%d", max(dp[n][0], max(dp[n][1], dp[n][2])));

    return 0;
}