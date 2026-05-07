#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug

using namespace std;
typedef long long ll;

namespace FileIO{
    void Test(string s){
        freopen((s+".in").c_str(),"r",stdin);
        freopen("test.out","w",stdout);
    }
    void File(string s){
        freopen((s+".in").c_str(),"r",stdin);
        freopen((s+".out").c_str(),"w",stdout);
    }
}

namespace FastIO{
    const int BUF_L=1<<20;
    char ibuf[BUF_L];
    char obuf[BUF_L];
    char *po=obuf;
    char *p1=ibuf,*p2=ibuf;

    inline char getchar(){
        if(p1==p2){
            p2=ibuf+fread(ibuf,1,BUF_L,stdin),p1=ibuf;
            if(p1==p2) return EOF;
        }
        return *p1++;
    }

    inline void flush(){
        fwrite(obuf,1,po-obuf,stdout);
        po=obuf;
    }

    inline void putchar(char ch){
        if(po==obuf+BUF_L) flush();
        *po++=ch;
    }

    void read(){}

    template<typename T>
    void read(T &res){
        bool neg=0;
        res=0;
        char ch=getchar();
        while(ch<'0'||ch>'9'){
            if(ch=='-') neg=1;
            ch=getchar();
        }
        while(ch>='0'&&ch<='9'){
            res=(res<<3)+(res<<1)+(ch^48);
            ch=getchar();
        }
        if(neg) res=-res;
    }

    void read(string &res){
        char ch=getchar();
        res="";
        while(ch==' '||ch=='\n') ch=getchar();
        while(ch!=' '&&ch!='\n'&&ch!=EOF){
            res+=ch;
            ch=getchar();
        }
    }

    void read(char &res){
        char ch=getchar();
        while(ch==' '||ch=='\n') ch=getchar();
        res=ch;
    }

    void read(char *c){
        int ip=0;
        char ch=getchar();
        while(ch==' '||ch=='\n') ch=getchar();
        while(ch!=' '&&ch!='\n'&&ch!=EOF) c[ip++]=ch,ch=getchar();
        c[ip]='\0';
    }

    template<typename... Arg>
    void read(Arg&... args){
        (read(args),...);
    }

    void write(){}

    template<typename T>
    void write(T tp){
        if(tp<0){
            putchar('-');
            tp=-tp;
        }
        if(tp==0){
            putchar('0');
            return;
        }
        static char buf[32];
        int idx=0;
        while(tp){
            buf[idx++]=tp%10+'0';
            tp/=10;
        }
        while(idx) putchar(buf[--idx]);
    }

    void write(char ch){
        putchar(ch);
    }

    void write(const string &s){
        for(char ch:s) putchar(ch);
    }

    void write(const char* s){
        for(int i=0;s[i];i++) putchar(s[i]);
    }

    template<typename... Arg>
    void write(const Arg&... args){
        (write(args),...);
    }
}

using FastIO::read;
using FastIO::write;

const int N = 8e4 + 10;

int T, n, m, o;
int lastans;
int a[N], tmp[N];
bool vis[N];

namespace PST {
    struct Node {
        int sum;
        int l, r;
    };

    int num;
    int root[N];
    Node node[N << 9];

    inline int Build(int l, int r) {
        int p = ++num;
        if (l == r) return p;
        int mid = l + r >> 1;
        Build(l, mid);
        Build(mid + 1, r);
        return p;
    }

    inline int Insert(int l, int r, int val, int ver) {
        int p = ++num;
        node[p] = node[ver];
        node[p].sum++;
        if (l == r) return p;
        int mid = l + r >> 1;
        if (val <= mid) node[p].l = Insert(l, mid, val, node[ver].l);
        if (mid + 1 <= val) node[p].r =  Insert(mid + 1, r, val, node[ver].r);
        return p;
    }

    inline int Query(int l, int r, int pos, int x, int y, int pre1, int pre2) {
        if (l == r) {
            return tmp[l];
        }
        int sizl = node[node[x].l].sum + node[node[y].l].sum - node[node[pre1].l].sum - node[node[pre2].l].sum;
        int mid = l + r >> 1;
        if (pos <= sizl) return Query(l, mid, pos, node[x].l, node[y].l, node[pre1].l, node[pre2].l);
        else return Query(mid + 1, r, pos - sizl, node[x].r, node[y].r, node[pre1].r, node[pre2].r);
    }
} using namespace PST;

namespace UnionFind {
    int father[N];

    inline int Find(int x) {
        if (father[x] == x) return x;
        return father[x] = Find(father[x]);
    }
} using namespace UnionFind;

namespace Edge {
    const int K = 20;

    int cnt;
    int head[N], to[N << 1], nxt[N << 1];
    int siz[N], dep[N];
    int st[N][K];

    inline void Add(int u, int v) {
        to[++cnt] = v;
        nxt[cnt] = head[u];
        head[u] = cnt;
    }

    inline void Dfs(int u, int fa, int rt) {
        siz[rt]++;
        vis[u] = true;
        dep[u] = dep[fa] + 1;
        st[u][0] = father[u] = fa;
        root[u] = Insert(1, n, a[u], root[fa]);
        for (int i = 1; i < K; i++) st[u][i] = st[st[u][i - 1]][i - 1];
        int v;
        for (int i = head[u]; i; i = nxt[i]) {
            v = to[i];
            if (v == fa) continue;
            Dfs(v, u, rt);
        }
    }

    inline int Lca(int x, int y) {
        if (dep[x] < dep[y]) swap(x, y);
        for (int i = K - 1; i >= 0; i--) {
            if (dep[st[x][i]] >= dep[y]) {
                x = st[x][i];
            }
        }
        if (x == y) return x;
        for (int i = K - 1; i >= 0; i--) {
            if (st[x][i] != st[y][i]) {
                x = st[x][i];
                y = st[y][i];
            }
        }
        return st[x][0];
    }
} using namespace Edge;

signed main() {
    read(T, n, m, o);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
        tmp[i] = a[i];
        father[i] = i;
    }
    sort(tmp + 1, tmp + n + 1);
    int len = unique(tmp + 1, tmp + n + 1) - tmp - 1;
    for (int i = 1; i <= n; i++) a[i] = lower_bound(tmp + 1, tmp + len + 1, a[i]) - tmp;
    int x, y, z;
    for (int i = 1; i <= m; i++) {
        read(x, y);
        Add(x, y);
        Add(y, x);
        // printf("%d %d\n", x, y);
    }
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            Dfs(i, 0, i);
            father[i] = i;
        }
    }
    root[0] = Build(1, n);
    int lca, fax, fay;
    char c;
    for (int i = 1; i <= o; i++) {
        read(c);
        if (c == 'Q') {
            read(x, y, z);
            x ^= lastans;
            y ^= lastans;
            z ^= lastans;
            lca = Lca(x, y);
            lastans = Query(1, n, z, root[x], root[y], root[lca], root[st[lca][0]]);
            write(lastans);
            write("\n");
        }
        if (c == 'L') {
            read(x, y);
            x ^= lastans;
            y ^= lastans;
            Add(x, y);
            Add(y, x);
            fax = Find(x);
            fay = Find(y);
            if (siz[fax] < siz[fay]) {
                swap(x, y);
                swap(fax, fay);
            }
            Dfs(y, x, fax);
        }
    }
    FastIO::flush();
    return 0;
}