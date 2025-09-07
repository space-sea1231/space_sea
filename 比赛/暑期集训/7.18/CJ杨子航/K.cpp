#include <iostream>
#include <stdio.h>
// #define __Debug

using namespace std;
typedef long long ll;

const int N=1e6+10;
const int M=70;

ll t, n;
int a[N];
int cnt[M], sum[N];

void Init(){
    for (int i=1; i<=n; i++){
        sum[i]=0;
    }
    for (int i=1; i<=64; i++){
        cnt[i]=0;
    }
    return;
}
void Decompose(int a){
    int now=1;
    while (a>0){
        if (a&1==true){
            cnt[now]++;
        }
        now++;
        a=a>>1;
    }
    return;
}
void Decompose1(int a, int id){
    int now=1;
    while (a>0){
        if (a&1==true&&cnt[now]%2==true){
            sum[id]=sum[id]+(1<<(now-1));
        }
        now++;
        a=a>>1;
    }
    return;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> t;
    while (t--){
        Init();
        cin >> n;
        for (int i=1; i<=n; i++){
            cin >> a[i];
            Decompose(a[i]);
        }
        // for (int i=1; i<=n; i++){
        //     Decompose1(a[i], i);
        // }
        int ans=0;
        for (int i=1; i<=64; i++){
            if (cnt[i]%2==1){
                ans=ans+(1<<(i-1));
            }
            #ifdef __Debug
                printf("%d ", cnt[i]);
            #endif
        }
        #ifdef __Debug
            printf("\n");
        #endif
        printf("%d\n", ans);
    }
    return 0;
}
/*
0110
0101
0111

0101
1001
4+8=12
4+0=4
*/