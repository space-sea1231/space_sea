#include <bits/stdc++.h>
using namespace std;
int Random(int l, int r) {
    return rand() % (r - l + 1) + l;//生成随机数
}
int fa[20];
int Find(int x) {
    if (x == fa[x]) return x;
    return fa[x] = Find(fa[x]);
}
int main() {
    freopen("data.in", "w", stdout);
    srand(time(NULL));//随机种子
    int n = Random(1, 10);
    int m = Random(1, 10);
    printf("%d %d\n", n, m);
    for (int i = 1; i <= n; i ++) {
        fa[i] = i;
    }
    int cnt = 0;
    while (cnt < n-1) {
        int u = Random(1, n);
        int v = Random(1, n);
        int fu = Find(u);
        int fv = Find(v);
        if (fu != fv) {
            printf("%d %d\n", u, v);
            fa[fu] = fv;
            cnt ++;
        }
    }
    for (int i = 1; i <= m; i ++) {
        int u = Random(1, n);
        int v = Random(1, n);
        printf("%d %d\n", u, v);
    }
    
    return 0;
}