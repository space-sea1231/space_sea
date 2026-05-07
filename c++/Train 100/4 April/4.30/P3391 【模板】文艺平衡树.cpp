#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define lson son[0]
#define rson son[1]

using namespace std;
typedef long long ll;

const int N = 1e5 + 10;

int n, m;

namespace SplayTree {
    struct Node {
        int fa;
        int sum, siz;
        bool rev;
        int son[2];
    };

    int root;
    int num;
    Node node[N << 2];
    
    void Up(int x) {
        node[x].siz = node[node[x].lson].siz + node[node[x].rson].siz + 1;
    }

    void Down(int x) {
        if (node[x].rev) {
            swap(node[x].lson, node[x].rson);
            node[node[x].lson].rev ^= true;
            node[node[x].rson].rev ^= true;
            node[x].rev = false;
        }
    }

    int Build(int l, int r, int fa) {
        if (l > r) return 0;
        int p = ++num;
        int mid = l + r >> 1;
        node[p].fa = fa;
        node[p].sum = mid;
        node[p].lson = Build(l, mid - 1, p);
        node[p].rson = Build(mid + 1, r, p);
        Up(p);
        return p;
    }

    int Getpos(int k) {
        int u = root;
        while (true) {
            Down(u);
            if (k <= node[node[u].lson].siz) u = node[u].lson;
            else {
                k -= node[node[u].lson].siz + 1;
                if (k == 0) return u;
                u = node[u].rson;
            }       
        }
    }

    bool Check(int x) {
        return x == node[node[x].fa].rson;
    }

    void Rotate(int x) {
        int y = node[x].fa, z = node[y].fa, k = Check(x);
        Down(y), Down(x);
        node[y].son[k] = node[x].son[k ^ true];
        if (node[x].son[k ^ true]) node[node[x].son[k ^ true]].fa = y;
        node[x].son[k ^ 1] = y;
        node[y].fa = x;
        node[x].fa = z;
        if (z) node[z].son[node[z].rson == y] = x;
        Up(y), Up(x);
    }

    void Splay(int x) {
        for (int i = node[x].fa; i = node[x].fa, i; Rotate(x)) {
            if (node[i].fa) Rotate(Check(x) == Check(i) ? i : x);
        }
        root = x;
    }

    void Splay(int x, int y) {
        for (int i = node[x].fa; i = node[x].fa, i && i != y; Rotate(x)) {
            if (node[i].fa && node[i].fa != y) Rotate(Check(x) == Check(i) ? i : x);
        }
        if (y == 0) root = x;
    }

    // void Splay(int x, int goal){
    //     while(node[x].fa != goal){
    //         int y=node[x].fa, z=node[y].fa;
    //         if(z != goal){
    //             Rotate(Check(x)==Check(y)?y:x);
    //         }
    //         Rotate(x);
    //     }
    //     if(goal == 0) root = x;
    // }

    void Reverse(int l, int r) {
        int L = Getpos(l - 1);
        int R = Getpos(r + 1);
        Splay(L);
        Splay(R, L);
        node[node[R].lson].rev ^= true;
    }

    void Dfs(int u) {
        if (!u) return;
        Down(u);
        Dfs(node[u].lson);
        if (1 <= node[u].sum && node[u].sum <= n) printf("%d ", node[u].sum);
        Dfs(node[u].rson);   
    }
} using namespace SplayTree;

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    root = Build(0, n + 1, 0);
    for (int i = 1; i <= m; i++) {
        int l, r;
        cin >> l >> r;
        Reverse(l + 1, r + 1);
    }
    Dfs(root);
    return 0;
}