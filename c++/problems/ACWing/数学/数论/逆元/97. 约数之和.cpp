#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

const int N=2e2+10;
const int MOD=9901;

int a, b;
int cnt, ans=1, num;
int prime[N], count[N];

void Prime(int a){
    for (int i=2; i*i<=a; i++){
        if (a%i==0){
            prime[++num]=i;
            while (a%i==0){
                count[num]++;
                a/=i;
            }
        }
    }
    if (a>1){
        prime[++num]=a;
        count[num]++;
    }
}
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
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> a >> b;
    if (a==0){
        printf("0\n");
        return 0;
    }
    Prime(a);
    for (int i=1; i<=num; i++){
        if ((prime[i]-1)%MOD==0){
            ans=(ll)ans*(b*count[i]+1)%MOD;
        }
        else{
            ans=(ll)ans*(Pow(prime[i], b*count[i]+1)-1)*Pow(prime[i]-1, MOD-2)%MOD;
        }
    }
    printf("%d\n", (ans+MOD)%MOD);

    return 0;
}