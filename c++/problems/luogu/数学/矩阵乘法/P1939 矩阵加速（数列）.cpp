#include <iostream>
#include <stdio.h>
#define Mod(x) (x%MOD+MOD)%MOD
#define __Debug

using namespace std;
typedef long long ll;

const int N=10;
const int MOD=1e9+7;

int t, n;
ll a[N][N], sum[N][N], tmp[N][N];

void Init(){
    for (int i=1; i<=3; i++){
        for (int j=1; j<=3; j++){
            sum[i][j]=a[i][j]=0;
        }
    }
    for (int i=1; i<=3; i++){
        sum[i][i]=1;
    }
    a[1][1]=a[1][3]=a[2][1]=a[3][2]=1;
    return;
}
void Init1(){
    for (int i=1; i<=3; i++){
        for (int j=1; j<=3; j++){
            tmp[i][j]=0;
        }
    }
    return;
}
void Pow1(ll a[][N], ll b[][N]){
    Init1();
    for (int i=1; i<=3; i++){
        for (int j=1; j<=3; j++){
            for (int k=1; k<=3; k++){
                tmp[i][j]=Mod(tmp[i][j]+a[i][k]*b[k][j]);
            }
        }
    }
    for (int i=1; i<=3; i++){
        for (int j=1; j<=3; j++){
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

    cin >> t;
    while (t--){
        cin >> n;
        // if (n<=3){
        //     printf("1\n");
        //     continue;
        // }
        Pow();
        printf("%lld\n", sum[2][1]);
    }
    return 0;
}