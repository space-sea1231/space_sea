#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;
typedef long long ll;

int t = 1;
int n;
int fa[20];

int Random(int l, int r) {
    return (long long)rand() * rand() % (r - l + 1) + l;
}
int Find(int x) {
    if (fa[x] == x) return x;
    return fa[x] = Find(fa[x]);
}
int main() {
    srand((unsigned)time(0));
    printf("%d\n", t);
    while (t--) {
        int n = 5;
        printf("%d\n", n);
        for (int i = 1; i <= n; i++) fa[i] = i;
        for (int i = 1; i <= n; i++) {
            int a = Random(1, 9);
            printf("%d ", a);
        }
		printf("\n");
        for (int i = 1; i <= n; i++) {
            int b = Random(1, 9);
            printf("%d ", b);
        }
		printf("\n");
        printf("0 ");
        for (int i = 2; i <= n; i++) {
            int f = Random(1, i - 1);
            printf("%d ", f);
        }
    }
    return 0;
}