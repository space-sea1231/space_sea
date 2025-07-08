#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

const int N=1e5+10;

int t;
int a, b, c, d;
int cnt, sum;
int prime[N], factor[N];

void Primes(){
    for (int i=2; i<N; i++){
        if (factor[i]==0){
            factor[i]=i;
            prime[++cnt]=i;
        }
        for (int j=1; j<=cnt; j++){
            if (prime[j]>factor[i]||prime[j]*i>=N){
                break;
            }
            factor[prime[j]*i]=prime[j];
        }
    }
}
int PrimeNum(int x, int prime){
    int cnt=0;
    while (x%prime==0){
        cnt++;
        x/=prime;
    }
    return cnt;
}
int Pow(int a, int b){
    int sum=1;
    while (b){
        if (b&1){
            sum*=a;
        }
        a*=a;
        b>>=1;
    }
    return sum;
}
void Init(){
    sum=1;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    Primes();
    cin >> t;
    while (t--){
        Init();
        cin >> a >> c >> b >> d;
        for (int i=1; i<=cnt&&prime[i]<=d; i++){
            if (d%prime[i]==0){
                int ma=PrimeNum(a, prime[i]);
                int mb=PrimeNum(b, prime[i]);
                int mc=PrimeNum(c, prime[i]);
                int md=PrimeNum(d, prime[i]);
                #ifdef __Debug
                    printf("Debug1: %d %d %d %d %d\n", prime[i], ma, mc, mb, md);
                #endif
                if (ma==mc&&mb==md&&mc<=md){
                    sum*=(md-mc+1);
                }
                if (ma<mc||mb>md||mc>md){
                    sum=0;
                }
                d/=Pow(prime[i], md);
            }
        }
        if (d>1){
            int ma=PrimeNum(a, d);
            int mb=PrimeNum(b, d);
            int mc=PrimeNum(c, d);
            int md=PrimeNum(d, d);
            if (ma==mc&&mb==md&&mc<=md){
                sum*=(md-mc+1);
            }
            if (ma<mc||mb>md||mc>md){
                sum=0;
            }
        }
        printf("%d\n", sum);
    }
    return 0;
}