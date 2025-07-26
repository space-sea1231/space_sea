#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

const int N=2e6+10;
const int MOD=1e9+7;

int n;
int sum[N];
bool flag1=true, flag2=true;

int Pow(int a, int b){
    int sum=1;
    while (b){
        if (b&1){
            sum=((ll)sum*a)%MOD;
        }
        a=((ll)a*a)%MOD;
        b>>=1;
    }
    return sum;
}
void Go(){
    sum[1]=1;
    for (int i=2; i<=n; i++){
        sum[i]=((ll)sum[i-1]*i)%MOD;
    }
}
int Get(){
    int tot=1;
    for (int i=3; i<=n; i++){
        tot=((ll)tot*i%MOD+sum[i-1])%MOD;
    }
    return tot;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i=2; i<=n; i++){
        int x;
        cin >> x;
        if (x!=1) flag1=false;
        if (x!=i-1) flag2=false;
    }
    if (flag1==true){
        printf("%d\n", n-1);
    }
    else if (flag2==true){
        Go();
        printf("%lld\n", ((ll)Get()*Pow(sum[n-1], MOD-2))%MOD);
        printf("%d %d\n", Get(), sum[n-1]);
    }
    return 0;
}