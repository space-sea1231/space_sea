#include <iostream>
#include <stack>

using namespace std;
typedef long long ll;

const int N=5;
const int M=20;

bool vis[M];

inline int Random(int l, int r){
    return rand()%(r-l+1)+l;//生成随机数
}
signed main(){
    srand(time(NULL));//随机种子
    
    int n=N, m=Random(0, M);
    printf("%d\n", n);
    for (int i=2; i<=n; i++){
        int v=Random(1, i-1);
        int w=Random(0, M);
        printf("%d %d %d\n", i, v, w);
    }
    printf("%d\n", m);

    return 0;
}