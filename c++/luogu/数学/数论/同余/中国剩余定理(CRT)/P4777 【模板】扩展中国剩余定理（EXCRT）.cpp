#include <iostream>
#include <stdio.h>
// #define __Debug
#define int long long

using namespace std;
typedef long long ll;
typedef __int128 i128;

int n;
i128 x, y;
i128 sum=1, ans;

int Exgcd(int a, int b, i128 &x, i128 &y){
    if (b==0){x=1, y=0; return a;}
    int d=Exgcd(b, a%b, x, y);
    int z=x; x=y, y=z-y*(a/b);
    return d;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i=1; i<=n; i++){
        int a, m;
        cin >> m >> a;
        int d=Exgcd(sum, m, x, y);
        #ifdef __Debug
            printf("Debug: %dx%c%dy=%d\n", sum, -m<0?'-':'+', abs(m), a-ans);
        #endif
        if ((a-ans)%d==0){
            #ifdef __Debug
                printf("i=%d x=%d y=%d\n", i, x*(a-ans)/d, y*(a-ans)/d);
            #endif
            x=x*(a-ans)/d;
            x=(x%(m/d)+(m/d))%(m/d);
            ans=(i128)ans+x*sum;
            sum=(i128)m/d*sum;
            ans=(ans%sum+sum)%sum;
        }
        else{
            printf("-1\n");
            return 0;
        }
    }
    printf("%lld\n", (ll)ans);

    return 0;
}