#include <iostream>
#include <stdio.h>
#include <vector>
// #define __Debug
#define int long long

using namespace std;
typedef long long ll;

const int N=1e6+10;

int t;
int a, b, c, d;
int siz, top, ans;
int prime[N], factor[N];
vector<pair<int, int> > fac;

void Primes(){
    for (int i=2; i<N; i++){
        if (factor[i]==0){
            factor[i]=i;
            prime[++top]=i;
        }
        for (int j=1; j<=top; j++){
            if (prime[j]>factor[i]||prime[j]*i>=N){
                break;
            }
            factor[prime[j]*i]=prime[j];
        }
    }
}
int Gcd(int a, int b){
    while (b^=a^=b^=a%=b);
    return a;
}
ll Lcm(ll a, ll b){
    return a*b/Gcd(a, b);
}
void Search(int dep, int sum){
    if (dep==siz){
        if (Gcd(sum, a)==b&&Lcm(sum, c)==(ll)d){
            #ifdef __Debug
                printf("Debug3: %d\n", sum);
            #endif
            ans++;
        }
        return;
    }
    int tmp=1;
    for (int i=0; i<=fac[dep].second; i++){
        Search(dep+1, sum*tmp);
        tmp*=fac[dep].first;
    }
}
void Init(){
    fac.clear();
    ans=0;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Primes();
    cin >> t;
    while (t--){
        Init();
        cin >> a >> b >> c >> d;
        int tmp=d;
        for (int i=1; i<=top&&prime[i]<=tmp; i++){
            int cnt=0;
            while (tmp%prime[i]==0&&tmp>0){
                cnt++;
                tmp/=prime[i];
            }
            if (cnt>0){
                fac.push_back(make_pair(prime[i], cnt));
                #ifdef __Debug
                    // printf("Debug1: %d %d\n", prime[i], cnt);
                #endif
            }
            #ifdef __Debug
                // printf("Debug2: %d %d %d\n", i, prime[i], tmp);
            #endif
        }
        siz=fac.size();
        Search(0, 1);
        printf("%d\n", ans);
    }

    return 0;
}