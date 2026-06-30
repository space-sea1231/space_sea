#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <queue>
#define __Debug

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 2e5 + 10;
const int M = 2e6 + 10;

namespace AC {
    const int K = 27;

    struct Node {
        int ru, fail;
        int ans, idx;
        int son[K];
    };

    Node node[M];
    int ans[N];
    int dfn, num;

    void Insert(string s, int &idx) {
        int len = s.size(), u = 0;
        for (int i = 0; i < len; i++) {
            int &son = node[u].son[s[i] - 'a'];
            if (!son) son = ++dfn;
            u = son;
        }
        if (!node[u].idx) node[u].idx = ++num;
        idx = node[u].idx;
    }
    void Build() {
        queue<int> q;
        for (int i = 0; i < 26; i++) if (node[0].son[i]) q.push(node[0].son[i]);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int i = 0; i < 26; i++) {
                if (node[u].son[i]) {
                    node[node[u].son[i]].fail = node[node[u].fail].son[i];
                    node[node[node[u].fail].son[i]].ru++;
                    q.push(node[u].son[i]);
                } else node[u].son[i] = node[node[u].fail].son[i];
            }
        }
    }
    void Query(string s) {
        int len = s.size(), u = 0;
        for (int i = 0; i < len; i++) {
            u = node[u].son[s[i] - 'a'];
            node[u].ans++;
        }
    }
    void Topu() {
        queue<int> q;
        for (int i = 0; i <= dfn; i++) if (!node[i].ru) q.push(i);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            ans[node[u].idx] = node[u].ans;
            int v = node[u].fail;
            node[v].ans += node[u].ans;
            if (!--node[v].ru) q.push(v);
        }
    }
} using namespace AC;
int n;
int idx[N];
string s;

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> s;
        Insert(s, idx[i]);
    }
    cin >> s;
    Build();
    Query(s);
    Topu();
    for (int i = 1; i <= n; i++) printf("%d\n", ans[idx[i]]);
    return 0;
}