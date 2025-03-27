#include <bits/stdc++.h>
using namespace std;
int Random(int l, int r) {
    return rand() % (r - l + 1) + l;//生成随机数
}
const int N = 20;
int fa[N];
bool vis[N];
char c[4] = {' ', '+', '-', '?'}; 
int Find(int x) {
    if (x == fa[x]) return x;
    return fa[x] = Find(fa[x]);
}
bool Check1(int n) {
    for (int i = 1; i <= n; i ++) {
        if (!vis[i]) return 0;
    }
    return 1;
}
bool Check2(int n) {
    for (int i = 1; i <= n; i ++) {
        if (vis[i]) return 0;
    }
    return 1;
}
int main() {
    freopen("data.in", "w", stdout);
    srand(time(NULL));//随机种子
    int n = Random(1, N);
    printf("%d\n", n);
    for (int i = 1; i <= n; i ++) {
        fa[i] = i;
    }
    int cnt = 0;
    while (cnt < n-1) {
        int u = Random(1, n);
        int v = Random(1, n);
        int w = Random(1, n);
        int fu = Find(u);
        int fv = Find(v);
        if (fu != fv) {
            printf("%d %d %d\n", u, v, w);
            fa[fu] = fv;
            cnt ++;
        }
    }
    int m = Random(1, N);
    printf("%d\n", m);
    for (int i = 1; i <= m; i ++) {
        int opt = Random(1, 3);
        if (Check1(n)) opt = 2;
        if (Check2(n)) opt = 1;
        printf("%c ", c[opt]);
        if (opt == 1) {
            int x;
            while (vis[x = Random(1, n)]);
            vis[x] = 1;
            printf("%d\n", x);
        }
        if (opt == 2) {
            int x;
            while (!vis[x = Random(1, n)]);
            vis[x] = 0;
            printf("%d\n", x);
        }
        if (opt == 3) {
            printf("\n");
        }
    }
    
    return 0;
}