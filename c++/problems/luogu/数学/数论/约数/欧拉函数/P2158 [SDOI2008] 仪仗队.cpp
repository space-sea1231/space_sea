#include <iostream>
#include <stdio.h>
// #define __Debug

using namespace std;
typedef long long ll;

const int N=4e4+10;

int n;
int cnt, sum;
int phi[N];
int prime[N], factor[N];

void Primes(){
    for (int i=2; i<=n; i++){
        if (factor[i]==0){
            factor[i]=i;
            prime[++cnt]=i;
            phi[i]=i-1;
        }
        for (int j=1; j<=cnt; j++){
            if (prime[j]>factor[i]||prime[j]*i>n){
                break;
            }
            factor[i*prime[j]]=prime[j];
            phi[i*prime[j]]=phi[i]*(i%prime[j]==0?prime[j]:prime[j]-1);
            #ifdef __Debug
                printf("Debug: phi[%d]=%d\n", i*prime[j], phi[i*prime[j]]);
            #endif
        }
        sum+=phi[i];
        #ifdef __Debug
            printf("phi[%d]=%d\n", i, phi[i]);
        #endif
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;n--;
    Primes();
    printf("%d\n", (n==0?0:(sum<<1)+3));

    return 0;
}
/*
#include <iostream>
#include <stdio.h>
// #define __Debug

using namespace std;
typedef long long ll;

const int N=4e4+10;

int n;
int cnt, sum;
int phi[N];
int prime[N], factor[N];

void Primes(){
    for (int i=2; i<=n; i++){
        if (factor[i]==0){
            factor[i]=i;
            prime[++cnt]=i;
            phi[i]=i-1;
        }
        for (int j=1; j<=cnt; j++){
            if (prime[j]>factor[i]||prime[j]*i>=n){
                continue;
            }
            factor[i*prime[j]]=prime[j];
            phi[i*prime[j]]=phi[i]*(i%prime[j]==0?prime[j]:prime[j]-1);
        }
        sum+=phi[i];
        #ifdef __Debug
            printf("phi[%d]=%d\n", i, phi[i]);
        #endif
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    n--;
    Primes();
    printf("%d\n", (n==1?0:(sum<<1)+3));

    return 0;
}
*/