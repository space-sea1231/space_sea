#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define lson son[0]
#define rson son[1]

using namespace std;
typedef long long ll;

const int N = 1e5 + 1000;

int n, m, o;
string s[N << 1];

namespace SplayTree {
    struct Node{
        int fa, val;
        int siz;
        int son[2];
    };
    
    int root, num;
    Node node[N << 2];

    void Up(int x){
        node[x].siz = node[node[x].lson].siz + node[node[x].rson].siz + 1;
    }

    bool Check(int x){
        return x == node[node[x].fa].rson;
    }
    
    void Rotate(int x){
        int y = node[x].fa, z = node[y].fa, to = Check(x);
        node[y].son[to] = node[x].son[to ^ 1];
        if (node[x].son[to ^ 1]) node[node[x].son[to ^ 1]].fa = y;
        node[x].son[to ^ 1] = y;
        node[y].fa = x, node[x].fa = z;
        if (z) node[z].son[node[z].rson == y] = x;
        Up(y);
        Up(x);
    }

    void Splay(int x){
        for (int i = node[x].fa; i = node[x].fa, i; Rotate(x)){
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

    void Insert(int x){
        if (!root){
            node[++num].val = x;
            Up(num);
            root = num;
            return ;
        }
        int cur = root, last = 0;
        while (true){
            last = cur, cur = node[cur].son[x > node[cur].val];
            if (!cur){
                node[++num].val = x;
                node[num].fa = last;
                node[last].son[x > node[last].val] = num;
                Up(num);
                Up(last);
                Splay(num);
                return ;
            }
        }
    }

    int Getpos(int k) {
        int u = root;
        while (true) {
            if (k <= node[node[u].lson].siz) u = node[u].lson;
            else {
                k -= node[node[u].lson].siz + 1;
                if (k == 0) return u;
                u = node[u].rson;
            }       
        }
    }

    int Query(int x){
        int cur = root;
        while (true){
            if (node[cur].lson && x <= node[node[cur].lson].siz){
                cur = node[cur].lson;
                continue;
            }
            x -= node[node[cur].lson].siz + 1;
            if (x == 0){
                Splay(cur);
                return node[cur].val;
            }
            cur = node[cur].rson;
        }
    }
} using namespace SplayTree;

int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n;
    Insert(-1);
    Insert(100000000);
    for (int i = 1; i <= n; ++i) {
        cin >> s[i];
        Insert(i);
    }
    cin >> m;
    for (int i = 1; i <= m; i++) {
        int k;
        cin >> s[n + i] >> k;
        k += 2;
        int pos1 = Getpos(k);
        Splay(pos1);
        int pos2 = Getpos(k - 1);
        Splay(pos2, pos1);
        node[++num].fa = pos2;
        node[num].val = n + i;
        node[pos2].rson = num;
        Up(num);
        Up(pos2);
        Up(pos1);
    }
    cin >> o;
    for (int i = 1; i <= o; i++) {
        int k;
        cin >> k;
        k+=2;
        printf("%s\n", s[Query(k)].c_str());
    }
    return 0;
}