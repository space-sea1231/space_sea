#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <queue>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 2e3 + 10;

int n, k, b, m;
int a[N];
int stk[N];
int stk_tmp[N];
int top, top_tmp;
int pw[200];
queue<pair<int, int> > q;
struct Node {
    int val, pos;

    bool operator<(const Node &s) const {
        if (val == s.val) return pos < s.pos;
        return val < s.val;
    }
}; Node node[N];

void Search(int x) {
    if (x == n + 1) return ;
    for (int i = x; i <= n; i++) {

    }
}
void Go(int cur, int sum) {
    if (cur == top) {
        printf("%lld\n", sum + (ll)stk[cur] * pw[top - cur] % m);
        return ;
    }
    Go(cur + 1, sum + stk[cur] * pw[top - cur]);
    Go(cur + 1, sum);
}
signed main() {
    freopen("subsequence.in", "r", stdin);
    freopen("subsequence.out", "w", stdout);
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> k >> b >> m;
    int lg = 0;
    while ((1 << lg) - 1 < k) lg++;
    pw[0] = 1;
    for (int i = 1; i <= lg; i++) pw[i] = (ll)pw[i - 1] * b % m;
    int maxn = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        maxn = max(maxn, a[i]);
        node[i] = (Node){a[i], i};
    }
    sort(node + 1, node + n + 1);
    if (maxn <= 30) {
        cerr << 1;
        return 0;
    } else {
        int tmp[20][20];
        for (int i = n - 17; i <= n; i++) { // 取18位
            for (int j = i; j <= n; j++) {
                tmp[n - i + 1][n - j + 1] = a[j];
            }
        }
        for (int i = 1; i <= 18; i++) sort(tmp[i] + 1, tmp[i] + i + 1);
        // for (int i = 1; i <= 18; i++) {
        //     for (int j = 1; j <= i; j++) {
        //         printf("%d ", tmp[i][j]);
        //     }
        //     printf("\n");
        // }
        // printf("\n");
        int lst = 0;
        for (int i = 1; i <= n; i++) {
            // if (node[i].pos < lst) continue;
            // if (n - node[i].pos + 1 > k) {
            //     stk[++top] = node[i].val;
            //     lst = node[i].pos;
            // } else {
            //     Search(i);
            // }
            if (node[i].pos < lst) continue;
            if (n - node[i].pos + 1 > lg) {
                stk[++top] = node[i].val;
                lst = node[i].pos;
                lg--;
            } else {
                q.push(make_pair(i, top));
            }
        }
        
        int lst = 0;
        for (int i = 1; i <= n && k; i++) {
            if (node[i].pos < lst) continue;
            if ((1 << (n - node[i].pos + 1)) - 1 > k) {
                stk[++top] = node[i].val;
                lst = node[i].pos;
            } else {
                Search(i);
            }
        }
    }
    return 0;
}
/*

*/