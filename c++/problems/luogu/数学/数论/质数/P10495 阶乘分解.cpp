#include <iostream>
#include <stdio.h>

using namespace std;
typedef long long ll;

const int N=1e6+10;

int n;
int cnt;
int prime[N], factor[N];

void Primes(int n){
    for (int i=2; i<=n; i++){
        if (factor[i]==0){
            factor[i]=i;
            prime[++cnt]=i;
        }
        for (int j=1; j<=cnt; j++){
            if (prime[j]>factor[i]||i*prime[j]>n){
                break;
            }
            factor[i*prime[j]]=prime[j];
        }
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    Primes(n);
    for (int i=1; i<=cnt; i++){
        ll sum=1, cnt=0;
        for (int j=1; sum<=n; j++){
            sum*=prime[i];
            cnt+=n/sum;
        }
        printf("%lld %lld\n", prime[i], cnt);
    }
    return 0;
}