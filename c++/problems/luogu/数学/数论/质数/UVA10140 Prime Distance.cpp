#include <iostream>
#include <stdio.h>
#include <cmath>
// #define __Debug

using namespace std;

const int N=1e6+10;
const int INF=0x3f3f3f3f;

int l, r;
int cnt;
int prime[N], factor[N];
bool vis[N];

struct Ans{
    int l, r;
};
Ans mina, maxa;

void Primes(){
    for (int i=2; i<N; i++){
        if (factor[i]==0){
            factor[i]=i;
            prime[++cnt]=i;
            #ifdef __Debug
                // printf("Debug2: %d\n", i);
            #endif
        }
        for (int j=1; j<=cnt; j++){
            if (prime[j]>factor[i]||i*prime[j]>=N){
                break;
            }
            factor[i*prime[j]]=prime[j];
        }
    }
}
void Init(){
    for (int i=1; i<=r-l; i++){
        vis[i]=0;
    }
    mina.l=mina.r=-1;
    maxa.l=maxa.r=-1;
}
signed main(){
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    Primes();
    while (cin >> l >> r){
        Init();
        #ifdef __Debug
            cerr << "Debug1:\n";
        #endif
        for (int i=1; i<=cnt; i++){//2 17
            for (int j=max(2, (int)ceil((double)l/prime[i])); j<=r/prime[i]; j++){
                vis[prime[i]*j-l]=1;
                #ifdef __Debug
                    // printf("Debug4: %d %d\n", l, r);
                    // printf("Debug4: %lf %d\n", ceil((double)l/prime[i]), r/prime[i]);
                    printf("Debug3: %d %d %d\n", i, j, prime[i]*j);
                #endif
            }
        }
        #ifdef __Debug
            // for (int i=1; i<=8; i++){
            //     printf("Debug5: %d %d\n", i, prime[i]);
            // }
        #endif
        int pre=-1, minn=INF, maxn=-INF;
        for (int i=0; i<=r-l; i++){
            if (!vis[i]){
                #ifdef __Debug
                    printf("Debug1: %d\n", i+l);
                #endif
                if (pre==-1){
                    pre=i;
                    continue;
                }
                if (i-pre<minn){
                    minn=i-pre;
                    mina.l=pre;
                    mina.r=i;
                    #ifdef __Debug
                        printf("Debug6: %d %d\n", i, pre);
                    #endif
                }
                if (i-pre>maxn){
                    maxn=i-pre;
                    maxa.l=pre;
                    maxa.r=i;
                    #ifdef __Debug
                        printf("Debug7: %d %d\n", i, pre);
                    #endif
                }
                pre=i;
            }
        }
        if (mina.l!=-1){
            printf("%d,%d are closest, %d,%d are most distant.\n", mina.l+l, mina.r+l, maxa.l+l, maxa.r+l);
        }else{
            printf("There are no adjacent primes.");
        }
    }
    return 0;
}