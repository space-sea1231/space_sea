#include <bits/stdc++.h>
using namespace std;
const int N=1e2+10;
const int M=3e4+10;
int t, n;
int a[N], dp[M];
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> t;
    while (t--){
        memset(dp, 0, sizeof(dp));
        cin >> n;
        for (int i=1; i<=n; i++){
            cin >> a[i];
        }
        sort(a+1, a+n+1);
        int cnt=0;
        for (int i=1; i<=n; i++){
            if (dp[a[i]]){
                cnt++;
            }
            dp[a[i]]=1;
            for (int j=a[i]; j<=a[n]; j++){
                dp[j]=dp[j]|dp[j-a[i]];
            }
        }
        printf("%d\n", n-cnt);
    }

    return 0;
}