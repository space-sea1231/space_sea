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
        for (int i=m; i>=v; i--){
            dp[i]=max(dp[i], dp[i-v]+w);
        }
    }
    printf("%d\n", dp[m]);

    return 0;
}
