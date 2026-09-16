#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
// #include <vector>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e5 + 10;
const int M = 2e5 + 10;

int n, m;
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
namespace Per_Union_Found {
    int num;
    struct Node {
        int fa;
        int dep;
        Node *l, *r;
        void *operator new(size_t);
    };
    Node *root[M];
    
    void Build(Node *&p, int l, int r) {
        p = new Node();
        if (l == r) { p->fa = l; return; }
        int mid = l + r >> 1;
        Build(p->l, l, mid);
        Build(p->r, mid + 1, r);
    }
    Node *Query(Node *p, int l, int r, int pos) {
        if (l == r) return p;
        int mid = l + r >> 1;
        if (pos <= mid) return Query(p->l, l, mid, pos);
        else return Query(p->r, mid + 1, r, pos);
    }
    Node *Find(Node *p, int pos) {
        Node *fa = Query(p, 1, n, pos);
        if (fa->fa == pos) return fa;
        return Find(p, fa->fa);
    }
    void Merge(Node *q, Node *&p, int l, int r, int pos, int fa) {
        p = new Node(*q);
        if (l == r) {
            p->fa = fa;
            p->dep = q->dep;
            return;
        }
        int mid = l + r >> 1;
        if (pos <= mid) Merge(q->l, p->l, l, mid, pos, fa);
        else Merge(q->r, p->r, mid + 1, r, pos, fa);
    }
    void Update(Node *q, Node *&p, int l, int r, int pos) {
        p = new Node(*q);
        if (l == r) { p->dep++; return; }
        int mid = l + r >> 1;
        if (pos <= mid) Update(q->l, p->l, l, mid, pos);
        else Update(q->r, p->r, mid + 1, r, pos);
    }
    
    void CMerge(int x, int y, int v) {
        root[v] = root[v - 1];
        Node *fx = Find(root[v], x);
        Node *fy = Find(root[v], y);
        if (fx->fa != fy->fa) {
            if (fx->dep > fy->dep) swap(fx, fy);
            Merge(root[v - 1], root[v], 1, n, fx->fa, fy->fa);
            if (fx->dep == fy->dep) { Node *t = root[v]; Update(t, root[v], 1, n, fy->fa); }
        }
    }
} using namespace Per_Union_Found;
Node *p=(Node*)calloc(4000010,sizeof(Node));
int cnt;
void *Node::operator new(size_t siz){
    return p+(cnt++);
}

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    read(n, m);
    Build(root[0], 1, n);
    for (int i = 1; i <= m; i++) {
        int opt;
        read(opt);
        switch(opt) {
            case 1:{
                int x, y;
                read(x, y);
                CMerge(x, y, i);
                break;
            }
            case 2: {
                int k;
                read(k);
                root[i] = root[k];
                break;
            } 
            case 3:{
                int x, y;
                read(x, y);
                Node *fx = Find(root[i - 1], x);
                Node *fy = Find(root[i - 1], y);
                root[i] = root[i - 1];
                write(fx->fa == fy->fa, "\n");
            }
        }
    }
    FastIO::flush();
    return 0;
}