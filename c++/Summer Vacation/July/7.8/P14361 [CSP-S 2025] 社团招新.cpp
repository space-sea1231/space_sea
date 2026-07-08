#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <queue>
#define __Debug

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e5 + 10;

int t, n;
int cnt[4];
struct Node {
    int val, pos;
};

Node node[N];
priority_queue<int> q;

void Init() {
    for (int i = 1; i <= 3; i++) cnt[i] = 0;
    while (!q.empty()) q.pop();
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> t;
    while (t--) {
        Init();
        cin >> n;
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            int a, b, c;
            cin >> a >> b >> c;
            int maxn = max(a, max(b, c));
            if (a == maxn) {
                // cerr << "a " << a << " " << maxn << endl;
                node[i].val = max(b, c) - a;
                node[i].pos = 1; cnt[1]++; ans += a;
                // printf("Debuga: node[%d]=%d\n", i, node[i].pos);
            } else if (b == maxn) {
                // cerr << "b " << b << " " << maxn << endl;
                node[i].val = max(a, c) - b;
                node[i].pos = 2; cnt[2]++; ans += b;
                // printf("Debugb: node[%d]=%d\n", i, node[i].pos);
            } else if (c == maxn) {
                // cerr << "c " << c << " " << maxn << endl;
                node[i].val = max(a, b) - c;
                node[i].pos = 3; cnt[3]++; ans += c;
                // printf("Debugc: node[%d]=%d\n", i, node[i].pos);
            }
        }
        // cerr<<"\n";
        int pos = -1;
        for (int i = 1; i <= 3; i++) if (cnt[i] * 2 > n) pos = i;
        if (pos == -1) {
            printf("%d\n", ans);
            continue;
        }
        // for (int i = 1; i <= n; i++) printf("node[%d]=%d\n", i, node[i].pos);
        for (int i = 1; i <= n; i++) if (node[i].pos == pos) q.push(node[i].val);
        int tot = cnt[pos] - (n / 2);
        // cerr<<"t=" << t << " " << q.size() << endl;
        while (tot--) {
            // cerr<<t << " " << tot << " " << q.size() << endl;
            if (tot<-10) break;
            ans += q.top();
            q.pop();
        }
        printf("%d\n", ans);
    }
    return 0;
}