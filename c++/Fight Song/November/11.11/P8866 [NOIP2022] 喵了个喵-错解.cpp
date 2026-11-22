#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 3e2 + 10;
const int M = 2e6 + 10;

int T;
int n, m, k;
int top, pos, top1;
int a[M];
int tmp[N], tmp1[N];
bool vis[N], vis1[N];
pair<int, int> stk[N];

struct Ans {
    int id;
    int pos;
}; Ans ans[M];
struct Node {
    int l, r;
}; Node node[N];
struct Return {
    int id;
    pair<int, int> s;
}; Return re[N];
void Go(int l, int r) {
    if (l > r) return ;
    for (int i = l; i <= r; i++) {
        int id = a[i] + 1 >> 1;
        if (stk[id].first == 0) { // 栈是空的
            stk[id].first = a[i];
            ans[i] = (Ans){1, id};
        } else {
            if (!stk[id].second) { // 栈的大小为1
                if (pos == id) { 
                    ans[i] = (Ans){2, id};
                    stk[id].first = 0;
                    continue;
                }
                if (stk[id].first == a[i]) stk[id].first = 0;
                else stk[id].second = a[i];
                ans[i] = (Ans){1, id};
            } else {
                if (stk[id].first == a[i]) { // 栈底是
                    ans[i] = (Ans){2, id};
                    stk[id] = make_pair(stk[id].second, 0);
                } else { // 栈顶是
                    ans[i] = (Ans){1, id};
                    stk[id].second = 0;
                }
            }
        }
    }
}
int Find(int l, int r) {
    tmp1[top1 = 1] = n;
    top = 0; re[top1] = (Return){n, stk[n]};
    if (l > r) return n;
    for (int i = l; i <= r; i++) {
        int id = a[i] + 1 >> 1;
        if (!vis1[id]) {
            vis1[id] = true;
            tmp1[++top1] = id;
            re[top1] = (Return){id, stk[id]};
        }
        if (stk[id].first == 0) { // 栈是空的
            if (!vis[id]) {
                tmp[++top] = id;
                node[node[id].l].r = node[id].r;
                node[node[id].r].l = node[id].l;
            }
            stk[id].first = a[i];
            vis[id] = true;
        } else {
            if (!stk[id].second) {
                if (stk[id].first == a[i]) {
                    stk[id].first = 0;
                } else {
                    if (!vis[id]) {
                        tmp[++top] = id;
                        node[node[id].l].r = node[id].r;
                        node[node[id].r].l = node[id].l;
                    }
                    stk[id].second = a[i];
                    vis[id] = true;
                }
            } else {
                if (stk[id].first == a[i]) { // 栈底是
                    stk[id] = make_pair(stk[id].second, 0);
                } else { // 栈顶是
                    if (!vis[id]) {
                        tmp[++top] = id;
                        // if (i == 6) {
                        //     printf("Debug%d: %d %d\n", id, node[id].l, node[id].r);
                        // }
                        node[node[id].l].r = node[id].r;
                        node[node[id].r].l = node[id].l;
                    }
                    stk[id].second = 0;
                    vis[id] = true;
                }
            }
        }
    }
    for (int i = 1; i <= top1; i++) {
        vis1[tmp1[i]] = false;
        stk[re[i].id] = re[i].s;
    }
    int rev = node[0].r;
    for (int i = 1; i <= top; i++) {
        node[tmp[i]] = (Node){tmp[i] - 1, tmp[i] + 1};
        node[tmp[i] + 1] = (Node){tmp[i], tmp[i] + 2};
        node[tmp[i] - 1] = (Node){tmp[i] - 2, tmp[i]};
        vis[tmp[i]] = false;
    }
    return rev;
}
void Solve() {
    cin >> n >> m >> k;
    vector<int> anchor;
    for (int i = 0; i <= n; i++) {
        stk[i] = make_pair(0, 0);
        node[i] = (Node){i - 1, i + 1};
    }
    for (int i = 1; i <= m; i++) cin >> a[i];
    for (int i = 1; i <= m; i++) {
        if (a[i] == (n << 1) - 1) {
            anchor.emplace_back(i);
        }
    }
    Go(1, anchor.empty() ? m : anchor[0] - 1);
    for (int i = 0, lim = anchor.size(); i < lim; i += 2) {
        pos = Find(anchor[i] + 1, anchor[i + 1] - 1);
        Go(anchor[i] + 1, anchor[i + 1] - 1);
        ans[anchor[i]] = (Ans){1, pos};
        ans[anchor[i + 1]] = (Ans){1, pos};
        Go(anchor[i + 1] + 1, i + 2 < lim ? anchor[i + 2] - 1 : m);
    }
    int tot = 0;
    for (int i = 1; i <= m; i++) tot += ans[i].id;
    printf("%d\n", tot);
    for (int i = 1; i <= m; i++) {
        if (ans[i].id == 1) printf("%d %d\n", 1, ans[i].pos);
        if (ans[i].id == 2) {
            printf("%d %d\n", 1, n);
            printf("%d %d %d\n", 2, n, ans[i].pos);
        }
    }
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> T;
    while (T--) Solve();
    return 0;
}
/*
The best thing to buy today is a little time for yourself.
今天最值得买下的，是给自己的一点时间
*/