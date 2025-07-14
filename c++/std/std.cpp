#include <iostream>
#include <stdio.h>
#include <cmath>
#define __Debug

using namespace std;
typedef long long ll;
typedef long double ld;

int n, m;
ld x;

namespace Pts1_2_3{
    const int N=5e3+10;
    const int EXP=1e5;
    const double EPS=1e-8;
    ld pw[N], f[N];
    int a[N];
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> x;
    if (n){
        using namespace Pts1_2_3;
        x/=EXP, pw[0]=1;
        for (int i=1; i<=n; i++){
            cin >> a[i];
            pw[i]=pw[i-1]*x;
        }
        for (int i=1; i<=n; i++){
            for (int j=i; j>=1; j--){
                // f[i][j]=max(f[i-1][j], f[i-1][j-1]+a[i]*((pw[i]<EPS&&fabs(pw[i]-EPS)>(1e-12))?0:pw[j-1]));
                f[j]=max(f[j], f[j-1]+a[i]*pw[j-1]);
            }
        }
        for (int i=1; i<=m; i++){
            int a;
            cin >> a;
            printf("%.09LF\n", f[a]);
        }
    }
    return 0;
}