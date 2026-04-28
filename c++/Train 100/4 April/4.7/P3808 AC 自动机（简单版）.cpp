#include <iostream>
#include <stdio.h>
#include <queue>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 1e6 + 10;

int n;

namespace AC {
    static const int K = 26;
    
    struct Node {
        int son[K];
        int ans, fail;
        int cnt;
    };

    Node node[N];
    int ans[N];
    int dfn, num;
    
    void Insert(char c[]) {
        int u = 0;
        for (int i = 1; c[i]; i++) {
            int &son = node[u].son[c[i] - 'a'];
            if (!son) son = ++dfn;
            u = son;
        }
        node[u].cnt++;
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
                    q.push(node[u].son[i]);
                }
                else node[u].son[i] = node[node[u].fail].son[i];
            }
        }
    }
    int Query(char c[]) {
        int u = 0, rev = 0;
        for (int i = 1; c[i]; i++) {
            u = node[u].son[c[i] - 'a'];
            for (int j = u; j && node[j].cnt != -1; j = node[j].fail) {
                rev += node[j].cnt;
                node[j].cnt = -1;
            }
        }
        return rev;
    }
} using namespace AC;

char c[N];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> (c + 1);
        Insert(c);
        ans[i] = 0;
    }
    Build();
    cin >> (c + 1);
    printf("%d\n", Query(c));
    return 0;
}