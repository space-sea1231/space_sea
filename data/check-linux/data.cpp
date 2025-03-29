#include <bits/stdc++.h>
using namespace std;
int Random(int l, int r) {
    return rand() % (r - l + 1) + l;//生成随机数
}
const int N = 10;
int fa[N];
bool vis[N];
void Init() {
    for (int i = 1; i < N; i++) {
        fa[i] = i;
    }
}
int Find(int x) {
    if (x == fa[x]) return x;
    return fa[x] = Find(fa[x]);
}
int main() {
    freopen("data.in", "w", stdout);
    srand(time(NULL));//随机种子
    Init();
    int n = Random(1, N - 1);
    int m = Random(1, N - 1);
    printf("%d %d\n", n, m);
    
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
        int u = Random(1, n), v;
        while ((v = Random(1, n)) == u);
        printf("%d %d\n", u, v);
    }
    
    return 0;
}