#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#define __Debug

using namespace std;
typedef long long ll;

const int N=1e6+10;

int l;
int cnt, num;
int prime[N], factor[N];
vector<int> que;

int Gcd(int a, int b){
    while (b^=a^=b^=a%=b);
    return a;
}
int Pow(int a, int b, int mod){
    ll sum=1;
    while (b){
        if (b&1){
            sum=((ll)sum*a)%mod;
        }
        a=((ll)a*a)%mod;
        b>>=1;
    }
    return sum;
}
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
            factor[i*prime[j]]=prime[j];
        }
    }
}
int Phi(int x){
    int sum=x;
    for (int i=1; i<=cnt; i++){
        if (x%prime[i]==0){
            sum=sum/prime[i]*(prime[i]-1);
            while (x%prime[i]==0){
                x/=prime[i];
            }
        }
    }
    if (x>1){
        sum=sum/x*(x-1);
    }
    return sum;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Primes();
    while (cin >> l, l!=0){
        num++;
        que.clear();
        ll n=(ll)l*9/Gcd(l, 8);
        ll sum=Phi(n);
        for (int i=1; i*i<=sum; i++){
            if (sum%i==0){
                que.push_back(i);
                if (i*i!=sum){
                    que.push_back(sum/i);
                }
            }
        }
        sort(que.begin(), que.end());
        bool flag=false;
        for (auto idx:que){
            if (Pow(10, idx, n)==1){
                flag=true;
                printf("Case %d: %d\n", num, idx);
                break;
            }
        }
        if (flag==false){
            printf("Case %d: %d\n", num, 0);
        }
    }
    return 0;
}