#include <bits/stdc++.h>
using namespace std;
int Random(int l, int r) {
    return rand() % (r - l + 1) + l;//生成随机数
}
int main() {
    freopen("data.in", "w", stdout);
    srand(time(NULL));//随机种子
    int n=10;
    int m=10;
    printf("%d %d\n", n, m);
    for (int i=1; i<=n; i++){
        int u=Random(1, n);
        printf("%d ", u);
    }
    printf("\n");
    for (int i=1; i<=m; i++){
        int x=Random(1, n);
        int y=Random(1, n);
        printf("%d %d\n", x, y);
    }

    return 0;
}