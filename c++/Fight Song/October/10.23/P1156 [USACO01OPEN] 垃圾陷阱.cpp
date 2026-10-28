#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int T = 1e3 + 10;
const int N = 1e2 + 10;

int n, m;
int f[N];

struct Node {
    int t, f, h;
    bool operator<(const Node &s) { return t < s.t; }
}; Node node[N];
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) cin >> node[i].t >> node[i].f >> node[i].h;
    sort(node + 1, node + m + 1);
    f[0] = 10;
    for (int i = 1; i <= m; i++) {
        for (int j = n; ~j; j--) {
            if (f[j] >= node[i].t) {
                if (j + node[i].h >= n) {
                    printf("%d\n", node[i].t);
                    return 0;
                }
                f[j + node[i].h] = max(f[j + node[i].h], f[j]);
                f[j] += node[i].f;
            }
        }
    }
    printf("%d\n", f[0]);
    return 0;
}