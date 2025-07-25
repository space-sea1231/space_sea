#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e6+10;
int n, m, k, ans, stay;
int last[N], sum[N], cnt[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m >> k;
    for (int i=1; i<=n; i++){
        int color, val;
        cin >> color >> val;
        if (val<=k){
            stay=i;
        }
        if (last[color]<=stay){
            cnt[color]=sum[color];
        }
        ans+=cnt[color];
        sum[color]++;
        last[color]=i;
    }
    printf("%lld\n", ans);

    return 0;
}