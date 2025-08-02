#include <iostream>
#include <cstring>

using namespace std;
typedef long long ll;

const int N = 10;
const int M = 5;

int Random(int l, int r){
    return rand() % (r - l + 1) + l;//生成随机数
}

signed main() {
    srand(time(NULL));//随机种子
    int n = N, m = N;
    printf("%d %d\n", n, m);
    for (int i = 1; i <= n; i++) {
        int a = Random(1, M);
        printf("%d ", a);
    }
    printf("\n");
    for (int i = 1; i <= m; i++) {
        int l, r;
        l = Random(1, n);
        while ((r = Random(1, n)) < l);
        printf("%d %d\n", l, r);
    }
    return 0;
}