#include<bits/stdc++.h>
#define int long long
using namespace std;
const int NR = 1e6 + 5;
const int MOD = 998244353;
int t;
int n;
int a[2 * NR];
int b[2 * NR];
int maxn,ans;
signed main(){
    freopen("wo.in","r",stdin);
    freopen("wob.out","w",stdout);
    cin >> t;
    while(t--){
        maxn = ans = 0;
        cin >> n;
        for(int i = 1;i <= 2 * n;i++){
            cin >> a[i];
            b[i] = i;
        }
        do{
            bool flag = 0;
            for(int i = 1;i <= 2 * n;i++){
                if(a[i] != b[i] && a[i] != 0){
                    flag = 1;
                    break;
                }
            }
            if(flag) continue;
            int sum = 0;
            for(int i = 1;i <= n;i++) sum += abs(b[2 * i] - b[2 * i - 1]);
            if(maxn < sum){
                maxn = sum;
                ans = 1;
            }
            else if(maxn == sum) ans++;
        }
        while(next_permutation(b + 1,b + 2 * n + 1));
        cout << ans << "\n";
    }
    return 0;
}