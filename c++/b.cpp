#include <iostream>
#include <stdio.h>
// #define __Debug
#define int long long

using namespace std;
typedef long long ll;

const int N=1e5+10;

int n;
int sum=0;
int cnt[N];

bool Check(int x, int y){
    return cnt[x]==y%10&&cnt[y]==x%10;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i=1; i<=n; i++){
        int tmp=i;
        while (tmp>=10){
            tmp=tmp/10;
        }
        cnt[i]=tmp;
    }
    #ifdef __Debug
        int tot=0;
        for (int i=1; i<=1991; i++){
            if (Check(i, 1991)){
                if (i==1991) tot++;
                else tot=tot+2;
                printf("Debug2: %d\n", i);
            }
        }
        printf("Debug1: %d\n", tot);
        return 0;
    #endif
    for (int i=1; i<=n; i++){
        for (int j=1; j<=i; j++){
            if (Check(i, j)){
                if (i==j) sum++;
                else sum=sum+2;
            }
        }
        printf("%lld:%lld\n", i, sum);
    }
    return 0;
}
//1991
//1xx1
//111