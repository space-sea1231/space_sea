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
const int N = 2e5 + 10;

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

int n, Q;
int a[N];
// int belong[N];
// int l[N], r[N];

// namespace SegmentTree {
//     struct Node {
//         int val, vis;
//     }; Node node[N << 2];

//     void Down(int p) {
//         if (!node[p].vis) return ;
//         node[p << 1].vis = node[p].vis;
//         node[p << 1].val = node[p].vis;
//         node[p << 1 | 1].vis = node[p].vis;
//         node[p << 1 | 1].val = node[p].vis;
//         node[p].vis = 0;
//     }
//     void Build(int p, int l, int r) {
//         if (l == r) {
//             node[p].val = belong[l];
//             return ;
//         }
//         int mid = l + r >> 1;
//         Build(p << 1, l, mid);
//         Build(p << 1 | 1, mid + 1, r);
//     }
//     void Update(int p, int l, int r, int L, int R, int w) {
//         if (L <= l && r <= R) {
//             node[p].vis = node[p].val = w;
//             return ;
//         }
//         Down(p);
//         int mid = l + r >> 1;
//         if (L <= mid) Update(p << 1, l, mid, L, R, w);
//         if (mid < R) Update(p << 1 | 1, mid + 1, r, L, R, w);
//     }
//     int Query(int p, int l, int r, int pos) {
//         if (l == r) {
//             return node[p].val;
//         }
//         Down(p);
//         int mid = l + r >> 1;
//         if (pos <= mid) return Query(p << 1, l, mid, pos);
//         if (mid < pos) return Query(p << 1 | 1, mid + 1, r, pos);
//         return 0;    
//     }
// } using namespace SegmentTree;
vector<int> q;
int Search() {
    q.clear();
    for (int i = 1; i <= n; i++) {
        if (q.empty() || a[i] > q.back()) q.emplace_back(a[i]);
        else {
            int p = lower_bound(q.begin(), q.end(), a[i]) - q.begin();
            // cerr<<q[p] << " " << a[i] << endl;
            q[p] = a[i];
        }
    }
    return (int)q.size();
}
signed main() {
    freopen("lis.in", "r", stdin);
    freopen("lis.out", "w", stdout);
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    read(n, Q);
    // int cnt = 1; l[1] = 1;
    bool flag = true;
    for (int i = 1; i <= n; i++) {
        read(a[i]);
        if (a[i] > 2) flag = false;
    }
    if (flag) {
        vector<int> q1, q2;
        for (int i = 1; i <= n; i++) {
            if (a[i] == 1) q1.emplace_back(i);
            if (a[i] == 2) q2.emplace_back(i);
        }
        int pos = 1;
        while (Q--) {
            char c;
            read(c);
            if (c == '>') pos++;
            if (c == '<') pos--;
            if (c == '!') {
                int x;
                read(x);
                if (a[pos] == 1) {
                    q1.erase(lower_bound(q1.begin(), q1.end(), pos));
                }
                if (a[pos] == 2) q2.erase(lower_bound(q2.begin(), q2.end(), pos));
                a[pos] = x;
                if (x == 1) q1.emplace_back(pos);
                if (x == 2) q2.emplace_back(pos);
                if (!q1.empty() && !q2.empty() && q1.front() < q2.back()) printf("2\n");
                else printf("1\n");
                // if (pos > 1 && Query(1, 1, n, pos) == Query(1, 1, n, pos - 1)) {
                //     if (a[pos - 1] < x) { // pos off

                //     }
                // }
                // if (pos < n && Query(1, 1, n, pos) == Query(1, 1, n, pos + 1)) {
                //     if (a[pos + 1] < x) { // pos off

                //     }
                // }
                // printf("%d\n", Search());
            }
        }
        return 0;
    }
    // for (int i = 1; i <= n; i++) {
    //     belong[i] = cnt;
    //     r[cnt]++;
    //     if (a[i] < a[i + 1]) {
    //         cnt++;
    //         l[cnt] = i + 1, r[cnt] = i;
    //     }
    // }
    // Build(1, 1, n);
    // #ifdef __Debug
    // for (int i = 1; i <= n; i++) printf("belong[%d]=%d\n", i, belong[i]);
    // for (int i = 1; i <= cnt; i++) printf("l[%d]=%d r[%d]=%d\n", i, l[i], i, r[i]);
    // #endif
    int pos = 1;
    while (Q--) {
        char c;
        read(c);
        if (c == '>') pos++;
        if (c == '<') pos--;
        if (c == '!') {
            int x;
            read(x);
            a[pos] = x;
            // if (pos > 1 && Query(1, 1, n, pos) == Query(1, 1, n, pos - 1)) {
            //     if (a[pos - 1] < x) { // pos off

            //     }
            // }
            // if (pos < n && Query(1, 1, n, pos) == Query(1, 1, n, pos + 1)) {
            //     if (a[pos + 1] < x) { // pos off

            //     }
            // }
            printf("%d\n", Search());
        }
    }
    return 0;
}
/*
1.Check erery val`s belong
2.Quick Change [l,r]`s belong
3.
*/