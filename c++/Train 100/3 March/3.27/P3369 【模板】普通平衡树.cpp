#include <iostream>
#include <stdio.h>
#define __Debug
#define lson son[0]
#define rson son[1]

using namespace std;
typedef long long ll;

const int N = 1e5 + 10;
int n;

namespace Treap {
    int num, root;
    struct Node {
        int father, val;
        int cnt, size;
        int son[2];
    };
    Node node[N];

    void Update(int x) {
        node[x].size = node[node[x].lson].size + node[node[x].rson].size + node[x].cnt;
        return;
    }
    bool Check(int x) {
        return x == node[node[x].father].rson;
    }
    void Clear(int x) {
        node[x].father = node[x].val = 0;
        node[x].size = node[x].cnt = 0;
        node[x].rson = node[x].lson = 0;
        return;
    }
    void New(int x) {
        node[++num].val = x;
        node[num].cnt++;
        return;
    }
    void Rotate(int x) {
        int y = node[x].father, z = node[y].father, to = Check(x);
        node[y].son[to] = node[x].son[to ^ 1];
        if (node[x].son[to ^ 1]) node[node[x].son[to ^ 1]].father = y;
        node[x].son[to ^ 1] = y;
        node[y].father = x, node[x].father = z;
        if (z) node[z].son[node[z].rson == y] = x;
        Update(x), Update(y);
        return;
    }
    void Splay(int x) {
        for (int i = node[x].father; i = node[x].father, i; Rotate(x)) {
            if (node[i].father) Rotate(Check(x) == Check(i)?i:x);
        }
        root = x;
        return;
    }
    void Insert(int x) {
        if (!root) {
            New(x);
            Update(num);
            root = num;
            return;
        }
        int cur = root, last = 0;
        while (1) {
            if (node[cur].val == x) {
                node[cur].cnt++;
                Update(cur);
                Update(last);
                Splay(cur);
                return;
            }
            last = cur, cur = node[cur].son[x > node[cur].val];
            if (!cur) {
                New(x);
                node[num].father = last;
                node[last].son[x > node[last].val] = num;
                Update(num);
                Update(last);
                Splay(num);
                return;
            }
        }
        return;
    }
    int Pre() {
        int cur = node[root].lson;
        if (!cur) return cur;
        while (node[cur].rson) cur = node[cur].rson;
        Splay(cur);
        return cur;
    }
    int Nxt() {
        int cur = node[root].rson;
        if (!cur) return cur;
        while (node[cur].lson) cur = node[cur].lson;
        Splay(cur);
        return cur;
    }
    int ValRank(int x) {
        int ans = 0, cur = root;
        while (1) {
            if (x < node[cur].val) {
                cur = node[cur].lson;
                continue;
            }
            ans += node[node[cur].lson].size;
            if (!cur) return ans + 1;
            if (node[cur].val == x) {
                Splay(cur);
                return ans + 1;
            }
            ans += node[cur].cnt;
            cur = node[cur].rson;
        }
        return -1;
    }
    int RankVal(int x) {
        int cur = root;
        while (1) {
            if (node[cur].lson && x <= node[node[cur].lson].size) {
                cur = node[cur].lson;
                continue;
            }
            x -= node[node[cur].lson].size + node[cur].cnt;
            if (x <= 0) {
                Splay(cur);
                return node[cur].val;
            }
            cur = node[cur].rson;
        }
        return -1;
    }
    void Delete(int x) {
        ValRank(x);
        if (node[root].cnt > 1) {
            node[root].cnt--;
            Update(root);
            return;
        }
        if (!node[root].lson && !node[root].rson) {
            Clear(root);
            root = 0;
            return;
        }
        if (!node[root].lson) {
            int cur = root;
            root = node[root].rson;
            node[root].father = 0;
            Clear(cur);
            return;
        }
        else if (!node[root].rson) {
            int cur = root;
            root = node[root].lson;
            node[root].father = 0;
            Clear(cur);
            return;
        }
        else {
            int cur = root;
            int tmp = Pre();
            node[node[cur].rson].father = tmp;
            node[tmp].rson = node[cur].rson;
            Clear(cur);
            Update(root);
            return;
        }
    }
}using namespace Treap;
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int opt, x;
        cin >> opt >> x;
        if (opt == 1) Insert(x);
        if (opt == 2) Delete(x);
        if (opt == 3) printf("%d\n", ValRank(x));
        if (opt == 4) printf("%d\n", RankVal(x));
        if (opt == 5) {
            Insert(x);
            printf("%d\n", node[Pre()].val);
            Delete(x);
        }
        if (opt == 6) {
            Insert(x);
            printf("%d\n", node[Nxt()].val);
            Delete(x);
        }
    }
    return 0;
}