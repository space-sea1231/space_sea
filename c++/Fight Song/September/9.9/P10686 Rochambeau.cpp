#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 5e2 + 10;
const int M = 2e3 + 10;

int n, m;
int a[M], b[M];
int fa[N << 2]; // x->me x*2->attack x*3->defend
bool pos[N];
char c[M];

int Find(int x) {
    if (fa[x] == x) return x;
    return fa[x] = Find(fa[x]);
}
inline void Solve() {
    if (n == 1 && m == 0) {
        printf("Player 0 can be determined to be the judge after 0 lines\n"); 
        return ;
    }
    for (int i = 1; i <= m; i++) {
        cin >> a[i] >> c[i] >> b[i];
        a[i]++, b[i]++;
        if (c[i] == '<') {
            swap(a[i], b[i]);
            c[i] = '>';
        }
        // printf("%d %c %d\n", a[i], c[i], b[i]);
    }
    memset(pos, 0, sizeof(pos));
    for (int judge = 1; judge <= n; judge++) {
        for (int i = 1; i <= n * 3; i++) fa[i] = i;
        bool flag = true;
        for (int i = 1; i <= m; i++) {
            if (a[i] == judge || b[i] == judge) continue;
            if (c[i] == '>') {
                if (Find(a[i]) == Find(b[i]) || Find(a[i]) == Find(b[i] + n)) {
                    flag = false;
                    break;
                }
                fa[Find(a[i])] = fa[Find(b[i] + n * 2)];
                fa[Find(a[i] + n)] = fa[Find(b[i])];
                fa[Find(a[i] + n * 2)] = fa[Find(b[i] + n)];
            }
            if (c[i] == '=') {
                if (Find(a[i]) == Find(b[i] + n) || Find(a[i]) == Find(b[i] + n * 2)) {
                    flag = false;
                    break;
                }
                fa[Find(a[i])] = fa[Find(b[i])];
                fa[Find(a[i] + n)] = fa[Find(b[i] + n)];
                fa[Find(a[i] + n * 2)] = fa[Find(b[i] + n * 2)];
            }
        }
        if (flag) pos[judge] = true;
    }
    int cnt = 0;
    for (int i = 1; i <= n; i++) cnt += pos[i];
    // for (int i = 1; i <= n; i++) printf("pos[%d]=%d\n", i, pos[i]);
    if (cnt == 1) {
        int refa = -1, refb = -1;
        int flag;
        for (int i = 1; i <= m; i++) {
            if (c[i] == '>') {
                if (Find(a[i]) == Find(b[i]) || Find(a[i]) == Find(b[i] + n)) {
                    if (refa == -1) {
                        refa = a[i];
                        refb = b[i];
                        continue;
                    }
                    if (refa == a[i] || refa == b[i]) { flag = i; break; }
                    if (refb == a[i] || refb == b[i]) { swap(refa, refb); flag = i; break; }
                }
                fa[Find(a[i])] = fa[Find(b[i] + n * 2)];
                fa[Find(a[i] + n)] = fa[Find(b[i])];
                fa[Find(a[i] + n * 2)] = fa[Find(b[i] + n)];
            }
            if (c[i] == '=') {
                if (Find(a[i]) == Find(b[i] + n) || Find(a[i]) == Find(b[i] + n * 2)) {
                    if (refa == -1) {
                        refa = a[i];
                        refb = b[i];
                        continue;
                    }
                    if (refa == a[i] || refa == b[i]) { flag = true; break; }
                    if (refb == a[i] || refb == b[i]) { swap(refa, refb); flag = true; break; }
                }
                fa[Find(a[i])] = fa[Find(b[i])];
                fa[Find(a[i] + n)] = fa[Find(b[i] + n)];
                fa[Find(a[i] + n * 2)] = fa[Find(b[i] + n * 2)];
            }
        }
        printf("Player %d can be determined to be the judge after %d lines\n", refa - 1, flag);
    } else if (cnt == 0) printf("Impossible\n");
    else printf("Can not determine\n");
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    while(cin >> n >> m) Solve();
    return 0;
}