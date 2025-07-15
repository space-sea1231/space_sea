#include <iostream>
#include <stack>

using namespace std;
typedef long long ll;

const int N=5;

inline int Random(int l, int r){
    return rand()%(r-l+1)+l;//生成随机数
}
signed main(){
    srand(time(NULL));//随机种子
    
    int n=N;
    printf("%d\n", n);
    for (int i=1; i<=n; i++){
        int x=Random(1, 10);
        for (int j=1; j<=x; j++){
            int opt=Random(0, 1);
            printf("%c", (opt==1?'(':')'));
        }
        printf("\n");
    }

    return 0;
}