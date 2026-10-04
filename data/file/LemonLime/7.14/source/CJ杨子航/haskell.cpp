#include <iostream>
#include <stdio.h>
// #define __Debug

using namespace std;
typedef long long ll;

int n;

namespace Pts2{
    const int N=1e3+10;
    
    bool a[N], b[N];
    int sum[N];
}
signed main(){
    freopen("haskell.in", "r", stdin);
    freopen("haskell.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    if (n){
        using namespace Pts2;
        for (int i=1; i<=n; i++){
            char c;
            cin >> c;
            a[i]=c-'0';
            sum[i]=sum[i-1]+a[i];
        }
        for (int i=1; i<=n; i++){
            char c;
            cin >> c;
            b[i]=c-'0';
        }
        #ifdef __Debug
            for (int i=1; i<=n; i++){
                printf("a[%d]=%d b[%d]=%d\n", i, a[i], i, b[i]);
            }
        #endif
        for (int i=1; i<=n; i++){
            bool flag=true;
            for (int l=1; l+i-1<=n; l++){//1 4
                int r=l+i-1;
                if (((sum[r]-sum[l-1]<<1)>i)!=b[r]){
                    // #ifdef __Debug
                    //     if (i==4){
                    //         printf("l=%d r=%d sum=%d\n", l, r, sum[r]-sum[l-1]);
                    //     }
                    // #endif
                    flag=false;
                    break;
                }
            }
            if (flag==true){
                printf("1");
            }
            else{
                printf("0");
            }
        }
    }
    return 0;
}