#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)2e9 + 1 : (int)1e18 + 1;
const int N = 1e6 + 10;
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
            if(p1==p2){
                return EOF;
            }
        }
        return *p1++;
    }
    inline void flush(){
        fwrite(obuf,1,po-obuf,stdout),po=obuf;
    }
    inline void putchar(const char ch){
        if(__builtin_expect(po==obuf+BUF_L,0)) flush();
        *po++=ch;
    }
    void read(){

    }
    template<typename T>void read(T &res){
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
    template<> void read(string &res){
        char ch=getchar();
        res="";
        while(ch==' '||ch=='\n'){
            ch=getchar();
        }
        while(ch!=' '&&ch!='\n'&&ch!=EOF){
            res+=ch;
            ch=getchar();
        }
    }
    template<> void read(char &res){
        char ch=getchar();
        res=' ';
        while(ch==' '||ch=='\n'){
            ch=getchar();
        }
        res=ch;
    }
    void read(char *c){
        int ip=0;
        char ch=getchar();
        while(ch==' '||ch=='\n'){
            ch=getchar();
        }
        while(ch!=' '&&ch!='\n'&&ch!=EOF){
            c[ip++]=ch;
            ch=getchar();
        }
        c[ip]='\0';
    }
    template<typename... Arg>void read(Arg&... args){
        initializer_list<int>{(read(args),0)...,0};
    }
    void write(){

    }
    template<typename T> void write(T tp){
        if(tp<0){
            putchar('-');
            tp=-tp;
        }
        if(tp==0){
            putchar('0');
            return ;
        }
        static char buf[32];
        int idx=0;
        while(tp){
            buf[idx++]=tp%10+'0';
            tp/=10;
        }
        while(idx) putchar(buf[--idx]);
    }
    template<> void write(char ch){
        putchar(ch);
    }
    template<> void write(const string &s){
        for(char ch:s){
            putchar(ch);
        }
    }
    void write(const char* s){
        for(int i=0;s[i]!='\0';i++){
            putchar(s[i]);
        }
    }
    template<typename... Arg>void write(const Arg&... args){
        initializer_list<int>{(write(args),0)...,0};
    }
}
using FastIO::read;
using FastIO::write;

int n, m;
int fa[N];
int ans[N];

struct Node {
    int pos, id;

    bool operator<(const Node &s) const {
        return pos < s.pos;
    }
}; Node node[N];
struct Bean {
    int val, pos, id;
    
    bool operator<(const Bean &s) const {
        return val > s.val;
    }
}; Bean bean[N];

namespace SegmentTree {
    struct NodeT {
        int val;
        int maxn, minn;
    }; NodeT tree[N << 2];
    
    void Down(int p) {
        tree[p << 1].val += tree[p].val;
        tree[p << 1].maxn += tree[p].val;
        tree[p << 1].minn += tree[p].val;
        tree[p << 1 | 1].val += tree[p].val;
        tree[p << 1 | 1].maxn += tree[p].val;
        tree[p << 1 | 1].minn += tree[p].val;
        tree[p].val = 0;
    }
    void Up(int p) {
        tree[p].maxn = max(tree[p << 1].maxn, tree[p << 1 | 1].maxn);
        tree[p].minn = min(tree[p << 1].minn, tree[p << 1 | 1].minn);
    }
    void Build(int p, int l, int r) {
        if (l == r) {
            tree[p].val = tree[p].maxn = tree[p].minn = node[l].pos;
            return ;
        }
        int mid = l + r >> 1;
        Build(p << 1, l, mid);
        Build(p << 1 | 1, mid + 1, r);
        Up(p);
    }
    int QueryL(int p, int l, int r, int val) {
        if (l == r) return l;
        int mid = l + r >> 1;
        Down(p);
        if (tree[p << 1 | 1].minn < val || (tree[p << 1 | 1].minn == val && tree[p << 1].maxn != val)) return QueryL(p << 1 | 1, mid + 1, r, val);
        else return QueryL(p << 1, l, mid, val);
    }
    int QueryR(int p, int l, int r, int val) {
        if (l == r) return l;
        int mid = l + r >> 1;
        Down(p);
        if (val < tree[p << 1].maxn || (val == tree[p << 1].maxn && tree[p << 1 | 1].minn != val)) return QueryR(p << 1, l, mid, val);
        else return QueryR(p << 1 | 1, mid + 1, r, val);
    }
    int Query(int p, int l, int r, int pos) {
        if (l == r) return tree[p].val;
        int mid = l + r >> 1;
        Down(p);
        if (pos <= mid) return Query(p << 1, l, mid, pos);
        else return Query(p << 1 | 1, mid + 1, r, pos);
    }
    void Update(int p, int l, int r, int L, int R, int val) {
        if (L > R) return;
        if (L <= l && r <= R) {
            tree[p].val += val;
            tree[p].maxn += val;
            tree[p].minn += val;
            return ;
        }
        Down(p);
        int mid = l + r >> 1;
        if (L <= mid) Update(p << 1, l, mid, L, R, val);
        if (mid < R) Update(p << 1 | 1, mid + 1, r, L, R, val);
        Up(p);
    }
} using namespace SegmentTree;
int Find(int x) {
    if (fa[x] == x) return x;
    return fa[x] = Find(fa[x]);
}

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    read(n);
    for (int i = 1; i <= n; i++) fa[i] = i;
    for (int i = 1; i <= n; i++) {
        read(node[i].pos);
        node[i].id = i;
    }
    sort(node + 1, node + n + 1);
    for (int i = 2; i <= n; i++)
        if (node[i].pos == node[i - 1].pos) {
            if (node[Find(i)].id < node[Find(i - 1)].id) fa[Find(i - 1)] = Find(i);
            else fa[Find(i)] = Find(i - 1);
        }
    Build(1, 1, n);
    read(m);
    for (int i = 1; i <= m; i++) {
        read(bean[i].val, bean[i].pos);
        bean[i].id = i;
    }
    sort(bean + 1, bean + m + 1);
    for (int i = 1; i <= m; i++) {
        int ql = QueryL(1, 1, n, bean[i].pos);
        int qr = QueryR(1, 1, n, bean[i].pos);
        int dl = bean[i].pos - Query(1, 1, n, ql);
        int dr = Query(1, 1, n, qr) - bean[i].pos;
        if (dl < 0) ql = 0, dl = INF;
        if (dr < 0) qr = n + 1, dr = INF;
        // printf("ql:dis[%d(%d)]=%d qr:dis[%d(%d)]=%d\n", ql, node[ql].id, dl, qr, node[qr].id, dr);
        int dis = min(dl, dr);
        Update(1, 1, n, 1, ql, dis);
        Update(1, 1, n, qr, n, -dis);
        if (dl == dr) {
            if (node[Find(ql)].id < node[Find(qr)].id) fa[Find(qr)] = Find(ql);
            else fa[Find(ql)] = Find(qr);
            ans[bean[i].id] = node[Find(ql)].id;
        } else ans[bean[i].id] = (dl < dr ? node[Find(ql)].id : node[Find(qr)].id);
    }
    for (int i = 1; i <= m; i++) printf("%d\n", ans[i]);
    return 0;
}
/*
ql:dis[107(11032)]=1000 qr:dis[108(34055)]=1000
*/