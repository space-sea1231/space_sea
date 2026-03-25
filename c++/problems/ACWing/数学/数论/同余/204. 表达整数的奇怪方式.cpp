#include <iostream>
#include <stdio.h>
// #define __Debug
#define int long long

using namespace std;
typedef long long ll;

int n, x, y;
int sum=1, ans;

int Exgcd(int a, int b, int &x, int &y){
    if (b==0){x=1, y=0; return a;}
    int d=Exgcd(b, a%b, x, y);
    int z=x; x=y, y=z-y*(a/b);
    return d;
}
int Gcd(int a, int b){
    while (b^=a^=b^=a%=b);
    return a;
}
int Lcm(int a, int b){
    return a/Gcd(a, b)*b;
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
            ans=(ans+x*sum);
            sum=Lcm(sum, m);//x=8 m=7
            ans=(ans%sum+sum)%sum;
        }
        else{
            printf("-1\n");
            return 0;
        }
    }
    while (ans<0){
        ans+=sum;
    }
    // if (sum<0){
        // printf("ddd:%lld\n", sum);
        // return 0;
    // }
    if (ans-sum>0){
        ans=ans-ans/sum*sum;
    }
    printf("%lld\n", ans);

    return 0;
}