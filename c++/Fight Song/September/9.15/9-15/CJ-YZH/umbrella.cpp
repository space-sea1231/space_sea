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
const int N = 2e6 + 10;
const int K = 20;

int n, m;
int root;
int fa[N][K];
int dep[N], ru[N], dep1[N];
vector<int> e[N], e1[N];
namespace fio {
    const int SZ=(1<<23); char ibuf[SZ],obuf[SZ],*is=ibuf,*it=is,*os=obuf; int num[50],len;
    char gc() { return (is==it&&(it=(is=ibuf)+fread(ibuf,1,SZ,stdin),is==it))?EOF:*is++; }
    void flush() { fwrite(obuf,1,os-obuf,stdout),os=obuf; }
    void pc(char c) { (os-obuf==SZ?flush():void()),*os++=c; }
    void rd(int &x) {
        x=0; char c=gc();
        while('0'>c||c>'9') c=gc();
        while('0'<=c&&c<='9') x=(x<<3)+(x<<1)+c-'0',c=gc();
    } 
    void wr(int x) {
        len=0;
        if(!x) num[len++]=0;
        while(x) num[len++]=x%10,x/=10;
        for(int i=len-1;i>=0;i--) pc(num[i]+'0');
    }
    struct A {
        A& operator>>(int &x) { rd(x); return *this; }
    } fin;
    struct B {
        B& operator<<(const char &c) { pc(c); return *this; }
        B& operator<<(const char *c) { for(int i=0;c[i]!='\0';i++) pc(c[i]); return *this; }
        B& operator<<(const int &x) { wr(x); return *this; }
    } fout;
}
using fio::fin;
using fio::fout;
void Dfs(int u) {
    for (int v:e[u]) {
        for (int i = 1; i < K; i++) fa[v][i] = fa[fa[v][i - 1]][i - 1];
        dep[v] = dep[u] + 1;
        Dfs(v);
    }
}
int LCA(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    for (int i = K - 1; ~i; i--) {
        if (dep[fa[x][i]] >= dep[y]) {
            x = fa[x][i];
        }
    }
    if (x == y) return x;
    for (int i = K - 1; ~i; i--) {
        if (fa[x][i] != fa[y][i]) {
            x = fa[x][i];
            y = fa[y][i];
        }
    }
    return fa[x][0];
}
void Dfs1(int u) {
    for (int v:e1[u]) {
        dep1[v] = dep1[u] + 1;
        Dfs1(v);
    }
}
bool Dfs2(int u, int k) {
    if (u == k) return true;
    for (int v:e1[u]) {
        if (Dfs2(v, k)) return true;
    }
    return false;
}
signed main() {
    freopen("umbrella.in", "r", stdin);
    freopen("umbrella.out", "w", stdout);
    // fin.tie(nullptr) -> ios::sync_with_stdio(false);
    fin >> n >> m;
    for (int i = 1; i <= (n << 1); i++) {
        fin >> fa[i][0];
        if (!fa[i][0]) root = i;
        e[fa[i][0]].emplace_back(i);
    }
    Dfs(root);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (LCA(i, j) == i + n) {
                // printf("%d %d %d\n", i, j, LCA(i, j));
                e1[i].emplace_back(j);
                ru[j]++;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (!ru[i]) Dfs1(i);
    }
    // cerr<<fa[3][0] << " " << dep[3] << "\n";
    for (int i = 1; i <= m; i++) {
        int a, b;
        fin >> a >> b;
        // cerr<<dep1[a] << " " << dep1[b] << "\n";
        if (dep1[a] > dep1[b]) swap(a, b);
        if (Dfs2(a, b)) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}