#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, m, sum_a, sum_b;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m;
    for (int i=0; i<n; i++){
        for (int j=0; j<m; j++){
            if (i==j){
                sum_a+=(n-i)*(m-j);
            }else{
                sum_b+=(n-i)*(m-j);
            }
        }
    }
    printf("%lld %lld", sum_a, sum_b);

    return 0;
}