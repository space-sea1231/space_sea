#include <iostream>
#include <stdio.h>
#define Mod(x) (x%MOD+MOD)%MOD
#define __Debug

using namespace std;
typedef long long ll;
typedef __int128 i128;

const int N=10;
const int MOD=1e9+7;

ll t, n;
i128 a[N][N], sum[N][N], tmp[N][N];

void Init(){
    for (int i=1; i<=2; i++){
        for (int j=1; j<=2; j++){
            sum[i][j]=a[i][j]=0;
        }
    }
    for (int i=1; i<=2; i++){
        sum[i][i]=1;
    }
    a[1][1]=a[1][2]=a[2][1]=1;
    return;
}
void Init1(){
    for (int i=1; i<=2; i++){
        for (int j=1; j<=2; j++){
            tmp[i][j]=0;
        }
    }
    return;
}
void Pow1(i128 a[][N], i128 b[][N]){
    Init1();
    for (int i=1; i<=2; i++){
        for (int j=1; j<=2; j++){
            for (int k=1; k<=2; k++){
                tmp[i][j]=Mod(tmp[i][j]+a[i][k]*b[k][j]);
            }
        }
    }
    for (int i=1; i<=2; i++){
        for (int j=1; j<=2; j++){
            a[i][j]=tmp[i][j];
        }
    }
    return;
}
void Pow(){
    Init();
    while (n>0){
        if (n&1==true){
            Pow1(sum, a);
        }
        Pow1(a, a);
        n=n>>1;
    }
    return;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    // if (n<=3){
    //     printf("1\n");
    //     continue;
    // }
    Pow();
    printf("%lld\n", (ll)sum[2][1]);
    return 0;
}