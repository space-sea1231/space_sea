#include <iostream>
#include <stdio.h>
#define __Debug
#define Mod(x) (x%MOD+MOD)%MOD

using namespace std;
typedef long long ll;

const int N=1e2+10;
const int MOD=1e9+7;

ll n, m;
ll a[N][N], sum[N][N], tmp[N][N];

void Init(){
    for (int i=1; i<=n; i++){
        sum[i][i]=1;
    }
    return;
}
void Init1(){
    for (int i=1; i<=n; i++){
        for (int j=1; j<=n; j++){
            tmp[i][j]=0;
        }
    }
    return;
}
void Pow1(ll a[][N], ll b[][N]){
    Init1();
    for (int i=1; i<=n; i++){
        for (int j=1; j<=n; j++){
            for (int k=1; k<=n; k++){
                tmp[i][j]=Mod(tmp[i][j]+a[i][k]*b[k][j]);
            }
        }
    }
    for (int i=1; i<=n; i++){
        for (int j=1; j<=n; j++){
            a[i][j]=tmp[i][j];
        }
    }
    return;
}
// void Pow1(){
//     Init1();
//     for (int i=1; i<=n; i++){
//         for (int j=1; j<=n; j++){
//             for (int k=1; k<=n; k++){
//                 tmp[i][j]=Mod(tmp[i][j]+sum[i][k]*a[k][j]);
//             }
//         }
//     }
//     for (int i=1; i<=n; i++){
//         for (int j=1; j<=n; j++){
//             sum[i][j]=tmp[i][j];
//         }
//     }
//     return;
// }
// void Pow2(){
//     Init1();
//     for (int i=1; i<=n; i++){
//         for (int j=1; j<=n; j++){
//             for (int k=1; k<=n; k++){
//                 tmp[i][j]=Mod(tmp[i][j]+a[i][k]*a[k][j]);
//             }
//         }
//     }
//     for (int i=1; i<=n; i++){
//         for (int j=1; j<=n; j++){
//             a[i][j]=tmp[i][j];
//         }
//     }
//     return;
// }
void Pow(){
    while (m>0){
        if (m&1==true){
            Pow1(sum, a);
            // Pow1();
        }
        Pow1(a, a);
        // Pow2();
        m=m>>1;
    }
    return;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i=1; i<=n; i++){
        for (int j=1; j<=n; j++){
            cin >> a[i][j];
        }
    }
    Init(); Pow();
    for (int i=1; i<=n; i++){
        for (int j=1; j<=n; j++){
            printf("%lld ", sum[i][j]);
        }
        printf("\n");
    }

    return 0;
}