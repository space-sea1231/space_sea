#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

const int N=10;

ll p, q, a1, a2, n, m;
ll a[N][N], sum[N][N], tmp[N][N];

void Init(){
    for (int i=1; i<=2; i++){
        for (int j=1; j<=2; j++){
            sum[i][j]=a[i][j]=0;
        }
    }
	sum[1][1]=a2;
    sum[1][2]=a1;
	a[1][1]=p;
	a[2][1]=q;
	a[1][2]=1;
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
void Pow1(ll a[N][N], ll b[N][N]){
    Init1();
    for (int i=1; i<=2; i++){
        for (int j=1; j<=2; j++){
            for (int k=1; k<=2; k++){
                tmp[i][j]=(tmp[i][j]+a[i][k]*b[k][j])%m;
            }
        }
    }
    for (int i=1; i<=2; i++){
        for (int j=1; j<=2; j++){
            a[i][j]=tmp[i][j]%m;
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

    cin >> p >> q >> a1 >> a2 >> n >> m;
    n--;
    // if (n<=3){
    //     printf("1\n");
    //     continue;
    // }
    Pow();
    printf("%lld\n", sum[1][2]);
    return 0;
}