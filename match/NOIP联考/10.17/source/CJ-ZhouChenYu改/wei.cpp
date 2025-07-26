#include<bits/stdc++.h>
using namespace std;
int t,tt;
int n;
int p[400005];
int siz,ans,sum;
int main(){
    freopen("wei.in","r",stdin);
    freopen("wei.out","w",stdout);
    cin >> t;
    tt = t;
    while(t--){
        ans = sum = siz = 0;
        cin >> n;
        for(int i = 1;i <= n;i++) cin >> p[i];
        p[n + 1] = 0;
        for(int i = 1;i <= n;i++){
            if(clock() >= 1.49 * CLOCKS_PER_SEC / tt) break;
            for(int j = 1;j <= n;j++){
                if(clock() >= 1.49 * CLOCKS_PER_SEC / tt) break;
                swap(p[i],p[j]);
                sum = siz = 0;
                for(int k = 1;k <= n + 1;k++){
                    if(p[k] >= p[k - 1]) siz++;
                    else{
                        sum += siz * (siz + 1) / 2;
                        siz = 1;
                    }
                }
                swap(p[i],p[j]);
                ans = max(ans,sum);
            }
        }
        cout << ans << "\n";
    }
    return 0;
}