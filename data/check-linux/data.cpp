#include <iostream>

using namespace std;

const int N=100;

inline int Random(int l, int r){
    return rand()%(r-l+1)+l;//生成随机数
}
signed main() {
    srand(time(NULL));//随机种子
    int n=10, m=10;
    printf("%d %d\n", n, m);
    for (int i=1; i<=n; i++){
        int x=Random(1, N);
        int y=Random(1, N);
        int w=Random(1, N);
        printf("%d %d %d\n", x, y, w);
    }
    for (int i=1; i<=m; i++){
        int sx=Random(1, N);
        int sy=Random(1, N);
        int fx=Random(1, N);
        int fy=Random(1, N);
        if (sx>fx){
            swap(sx, fx);
        }
        if (sy>fy){
            swap(sy, fy);
        }
        printf("%d %d %d %d\n", sx, sy, fx, fy);
    }

    return 0;
}