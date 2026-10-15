#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e4 + 10;
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
int T;
int n, m;
double f[N];

struct Node {
    int l, r, a;

    bool operator<(const Node &s) const {
        return (double) a / (r - l + 1) < (double) s.a / (s.r - s.l + 1);
    }
}; Node node[N];

double Max(double a, double b) {
    if (a > b) return a;
    return b;
}
signed main() {
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    read(T);
    while (T--) {
        read(n, m);
        for (int i = 1; i <= m; i++) f[i] = 0;
        // memset(f, 0, sizeof(f));
        for (int i = 1; i <= n; i++) read(node[i].l, node[i].r, node[i].a);
        sort(node + 1, node + n + 1);
        for (int i = 1; i <= n; i++) {
            for (int j = m; j >= node[i].r; j--) {
                // f[j] = max(f[j], f[j - node[i].r] + (double)(node[i].r - node[i].l + 1) / (node[i].r - node[i].l + 1) * node[i].a);
                // f[j] = Max(f[j], f[j - node[i].r] + (double)(node[i].r - node[i].l + 1) / (node[i].r - node[i].l + 1) * node[i].a);
                double tmp = f[j - node[i].r] + (double)(node[i].r - node[i].l + 1) / (node[i].r - node[i].l + 1) * node[i].a;
                if (tmp > f[j]) f[j] = tmp;
            }
            for (int j = node[i].r - 1; j >= node[i].l; j--) {
                // f[j] = max(f[j], (double)(j - node[i].l + 1) / (node[i].r - node[i].l + 1) * node[i].a);
                // f[j] = (double)(j - node[i].l + 1) / (node[i].r - node[i].l + 1) * node[i].a;
                // f[j] = Max(f[j], (double)(j - node[i].l + 1) / (node[i].r - node[i].l + 1) * node[i].a);
                double tmp = (double)(j - node[i].l + 1) / (node[i].r - node[i].l + 1) * node[i].a;
                if (tmp > f[j]) f[j] = tmp;
            }
            // if (i == 2) {
                // printf("Debug1:%.10lf\n", f[1000]);
            // }
        }
        printf("%.10lf\n", f[m]);
    }

    return 0;
}
/*
1
3 1000
114 514 555   1.39
444 666 666   3
231 241 222   22.2
*/