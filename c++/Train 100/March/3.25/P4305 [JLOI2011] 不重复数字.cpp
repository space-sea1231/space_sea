#include <iostream>
#include <stdio.h>
#include<cstring>
#define __Debug

using namespace std;
typedef long long ll;

int t, n;
struct Hash {
    static const int N = 5e6 + 10;
    static const int M = 999997;
    int top;
    int head[N];
    struct Node {
        int next;
        int key;
    };
    Node node[N];

    int Key(int key) { return (1ll*key%M + M ^ 114514) % M; }
    bool Get(int key) {
        for (int i = head[Key(key)]; i; i = node[i].next) {
            if (node[i].key == key) return 1;
        }
        return 0;
    }
    bool Add(int key) {
        if (Get(key)) return 0;
        node[++top] = (Node){head[Key(key)], key};
        head[Key(key)] = top;
        return 1;
    }
    void clear() {
        memset(head,0,sizeof(head));
        for (int i = 1; i <= top; i++) {
            node[i] = (Node){0, 0};
        }
        top=0;
        return;
    }
};
Hash table;

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            int key;
            cin >> key;
            if (table.Add(key)) printf("%d ", key);
        }
        printf("\n");
        table.clear();
    }
    return 0;
}