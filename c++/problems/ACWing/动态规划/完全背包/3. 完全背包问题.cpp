#include <bits/stdc++.h>
using namespace std;
const int N=1e3+10;
int n, m;
int dp[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m;
    for (int i=1; i<=n; i++){
        int v, w;
        cin >> v >> w;
        for (int j=v; j<=m; j++){
            dp[j]=max(dp[j], dp[j-v]+w);
        }
    }
    printf("%d\n", dp[m]);

    return 0;
}