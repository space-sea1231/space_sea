#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <stack>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
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

int n;
int pos[N];
struct Node {
    int val;
    int id;
    bool flag;

    bool operator<(const Node &s) const {
        return val < s.val;
    }
}; Node node[N << 1];

namespace Tree {
    int sum[N];

    int Lowbit(int x) {return x & -x;}
    void Add(int x, int y) {
        for (int i = x; i <= n; i += Lowbit(i)) sum[i] += y;
    }
    int Query(int x) {
        int rev = 0;
        for (int i = x; i; i -= Lowbit(i)) rev += sum[i];
        return rev;
    }
} using namespace Tree;
signed main() {
    freopen("cross.in", "r", stdin);
    freopen("cross.out", "w", stdout);
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> node[i].val;
        node[i].id = i;
        node[i].flag = 0;
    }
    for (int i = n + 1; i <= (n << 1); i++) {
        cin >> node[i].val;
        node[i].id = i - n;
        node[i].flag = 1;
    }
    sort(node + 1, node + (n << 1) + 1);
    // for (int i = 1; i <= (n << 1); i++) printf("%d:%d\n", node[i].flag, node[i].val);
    int cnta = 0, cntb = 0;
    for (int i = 1; i <= (n << 1); i++) {
        if (node[i].val == node[i + 1].val) {
            if (!node[i].flag && cntb > cnta) swap(node[i], node[i + 1]);
            if (node[i].flag && cntb < cnta) swap(node[i], node[i + 1]);
        }
        if (!node[i].flag) cnta++;
        else cntb++;
        
    }
    stack<int> a, b;
    for (int i = 1; i <= (n << 1); i++) {
        if (!node[i].flag) {
            if (!b.empty()) {
                pos[b.top()] = node[i].id;
                b.pop();
            } else a.push(node[i].id);
        }
        if (node[i].flag) {
            if (!a.empty()) {
                pos[node[i].id] = a.top();
                a.pop();
            } else b.push(node[i].id);
        }
    }
    // for (int i = 1; i <= n; i++) printf("%d ", pos[i]);
    // printf("\n");
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += Query(n) - Query(pos[i]);
        Add(pos[i], 1);
    }
    printf("%lld\n", ans);
    return 0;
}