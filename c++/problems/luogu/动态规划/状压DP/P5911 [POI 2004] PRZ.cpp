#include <bits/stdc++.h>
using namespace std;
const int N=20;
int n, m, l;
int t[N], w[N];
int T[1<<N], W[1<<N], dp[1<<N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> m >> n;
    l=(1<<n)-1;
    for (int i=1; i<=n; i++){
        cin >> t[i] >> w[i];
    }
    for (int i=0; i<=l; i++){
        for (int j=1; j<=n; j++){
            if (i&(1<<(j-1))){
                T[i]=max(T[i], t[j]);
                W[i]+=w[j];
            }
        }
    }
    memset(dp, 0x3f, sizeof(dp));
    dp[0]=0;
    for (int i=0; i<=l; i++){
        for (int j=i; ; j=i&(j-1)){
            if (W[i^j]<=m){
                dp[i]=min(dp[i], dp[j]+T[i^j]);
            }
            if (!j){
                break;
            }
        }
    }
    printf("%d\n", dp[l]);

    return 0;
}