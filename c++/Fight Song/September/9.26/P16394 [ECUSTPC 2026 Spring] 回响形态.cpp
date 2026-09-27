#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 3e5 + 10;

int T;
ll n, k;
int fil[N];
int ans[N];

int fa[N], fb[N]; 

int find_fa(int x) {
    if (x <= 0) return 0;
    return fa[x] == x ? x : fa[x] = find_fa(fa[x]);
}
int find_fb(int x) {
    if (x > n) return n + 1;
    return fb[x] == x ? x : fb[x] = find_fb(fb[x]);
}

void init_dsu(int n) {
    for (int i = 0; i <= n + 1; i++) {
        fa[i] = i;
        fb[i] = i;
    }
}

void remove_node(int x) {
    fa[x] = find_fa(x - 1);
    fb[x] = find_fb(x + 1);
}

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        cin >> n >> k;
        if (k < n * (n - 1) / 2 || k > (n - 1) * (n - 1)) {
            printf("-1\n");
            continue;
        }
        k -= n * (n - 1) / 2;
        for (int i = 1; i < n; i++) {
            if (k < (ll)i * (i + 1) / 2) {
                for (int j = 1; j < i; j++) fil[j] = i;
                for (int j = i; j < n; j++) fil[j] = j;
                k -= (ll)i * (i - 1) / 2;
                for (int j = i; j && k; j--) fil[j]++, k--;
                break;
            }
        }

        int minn = 1, maxn = 1; ans[1] = 1;
        init_dsu(n);
        remove_node(1);

        for (int i = 1; i < n; i++) {
            if (fil[i] > maxn - minn) {
                int cur = fil[i] + minn;
                maxn = cur;
                remove_node(cur);
                ans[i + 1] = cur;
            } else {
                int cur = find_fa(maxn - 1);
                ans[i + 1] = cur;
                remove_node(cur);
            }
        }
        for (int i = 1; i <= n; i++) printf("%d ", ans[i]); printf("\n");

        minn = n, maxn = n, ans[1] = n;
        init_dsu(n);
        remove_node(n);

        for (int i = 1; i < n; i++) {
            if (fil[i] > maxn - minn) {
                int cur = maxn - fil[i];
                minn = cur;
                remove_node(cur);
                ans[i + 1] = cur;
            } else {
                int cur = find_fb(minn + 1);
                ans[i + 1] = cur;
                remove_node(cur);
            }
        }
        for (int i = 1; i <= n; i++) printf("%d ", ans[i]); printf("\n");
    }
    return 0;
}