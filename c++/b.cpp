#include <iostream>
#include <stdio.h>
#include <queue>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 2e5 + 10;
const int M = 2e6 + 10;

int n;

namespace AC {
    static const int K = 26;
    
    struct Node {
        int son[K];
        int ans, fail;
        int ru, idx;
    };

    Node node[N];
    int ans[N];
    int dfn, num;
    
    void Insert(char c[], int &idx) {
        int u = 0;
        for (int i = 1; c[i]; i++) {
            int &son = node[u].son[c[i] - 'a'];
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
            int u = q.front();
            q.pop();
            for (int i = 0; i < 26; i++) {
                if (node[u].son[i]) {
                    node[node[u].son[i]].fail = node[node[u].fail].son[i];
                    node[node[node[u].fail].son[i]].ru++;
                    q.push(node[u].son[i]);
                }
                else node[u].son[i] = node[node[u].fail].son[i];
            }
        }
    }
    void Query(char c[]) {
        int u = 0;
        for (int i = 1; c[i]; i++) {
            u = node[u].son[c[i] - 'a'];
            node[u].ans++;
        }
    }
    void Topu() {
        queue<int> q;
        for (int i = 0; i <= dfn; i++) if (!node[i].ru) q.push(i);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            ans[node[u].idx] = node[u].ans;
            int v = node[u].fail;
            node[v].ans += node[u].ans;
            if (!--node[v].ru) q.push(v);
        }
    }
} using namespace AC;

char c[M];
int idx[N];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> (c + 1);
        Insert(c, idx[i]);
    }
    Build();
    cin >> (c + 1);
    Query(c);
    Topu();
    for (int i = 1; i <= n; i++) printf("%d\n", ans[idx[i]]);
    return 0;
}