#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;
typedef long double ld;

namespace Pts1_2_3{
    const int N=5e3+10;
    const int EXP=1e5;
    int n, m;
    ld x;
    ld pw[N];
    ld f[N][N];
    int a[N];
}
signed main(){
    using namespace Pts1_2_3;
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> x;
    x/=EXP, pw[0]=1;
    for (int i=1; i<=n; i++){
        cin >> a[i];
        pw[i]=pw[i-1]*x;
    }
    for (int i=1; i<=n; i++){
        f[i][0]=f[i-1][0];
        for (int j=1; j<=i; j++){
            f[i][j]=max(f[i-1][j], f[i-1][j-1]+a[i]*pw[j-1]);
        }
    }
    for (int i=1; i<=m; i++){
        int a;
        cin >> a;
        printf("%.09LF\n", f[n][a]);
    }
    return 0;
}