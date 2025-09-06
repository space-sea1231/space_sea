#include <iostream>
#include <stdio.h>
#include <cmath>
// #define __Debug
#define int long long

using namespace std;
typedef long long ll;

const int N=1e5+10;
const int M=1e2+10;

int n;
int top[N], low[N], mid[N], bits[N];
int pow10[M]={1, 10, 100, 1000, 10000, 100000, 1000000};
int sum[M]={1, 11, 111, 1111, 11111, 111111, 1111111};
signed main(){
    freopen("count.in", "r", stdin);
    freopen("count.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    /*Init*/
    for (int i=1; i<=n; i++){
        int tmp=i, cnt=0;
        while (tmp>=10){
            tmp=tmp/10;
            cnt++;
        }
        top[i]=tmp;
        low[i]=i%10;
        mid[i]=i%pow10[cnt]/10;
        bits[i]=max(0LL, cnt-1);
        #ifdef __Debug
            // printf("Debug: top[%d]=%d, low[%d]=%d, mid[%d]=%d\n", i, top[i], i, low[i], i, mid[i]);
        #endif
    }
    /*Solve*/
    int ans=0;
    for (int i=1; i<=n; i++){//2
        if (low[i]==top[i]){
            ans=ans+(mid[i]<<1)+1;
            if (bits[i]-1>=0){
                ans=ans+(sum[bits[i]-1]<<1);
            }
            if (i>=10) ans=ans+2;
        }
        if (low[i]>top[i]&&bits[i]-1>=0){
            ans=ans+(sum[bits[i]-1]<<1);
        }
        if (low[i]<top[i]&&low[i]*10+top[i]>10){
            ans=ans+(sum[bits[i]]<<1);
        }
        #ifdef __Debug
            printf("%d:%d\n", i, ans);
        #endif
    }
    printf("%lld\n", ans);

    return 0;
}
/*
axxb
bxxa
*/