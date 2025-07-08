#include <iostream>

using namespace std;
typedef long long ll;

const int N=10;
const int INF=1e7+10;
const int INTMAX=0x7fffffff;

inline int Random(int l, int r){
    return rand()%(r-l+1)+l;//生成随机数
}
signed main(){
    srand(time(NULL));//随机种子
    
    int n=N;
    printf("%d\n", n);
    while (n--){
        ll a, b, c, d;
        b=Random(1, INF);
        c=Random(1, INF);
        a=b*Random(1, INF);
        d=c*Random(1, INF);
        while ((a=b*Random(1, INF))>=INTMAX);
        while ((d=c*Random(1, INF))>=INTMAX);
        printf("%lld %lld %lld %lld\n", a, b, c, d);
    }

    return 0;
}