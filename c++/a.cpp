#include "stdio.h"
#include "algorithm"
#include "string.h"
using namespace std;
int a[11911111][30];
int b[11911111];
char c[999999];
int ll[999999];
int tot = 1, l;
void ppp() {
    int u = 1;
    int lll = strlen(c);

    for (int i = 0; i < lll; i++) {
        int t = c[i] - 'a' + 1;

        if (a[u][t])
            u = a[u][t];
        else {
            a[u][t] = ++tot;
            u = a[u][t];
        }
    }

    b[u] = 1;
}
void find(int i) {
    int u = 1;

    for (i; i < l; i++) {
        int t = c[i] - 'a' + 1;

        if (a[u][t])
            u = a[u][t];
        else
            break;

        if (b[u])
            ll[i + 1] = 1;
    }
}
int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    for (int i = 0; i < n; i++) {
        scanf("%s", c);
        ppp();
    }

    for (int i = 0; i < m; i++) {
        memset(ll, 0, sizeof(ll));
        scanf("%s", c);
        l = strlen(c);
        ll[0] = 1;

        for (int j = 0; j < l; j++) {
            if (ll[j])
                find(j);
        }

        for (int j = l; j >= 0; j--) {
            if (ll[j]) {
                printf("%d\n", j);
                break;
            }
        }
    }
}
