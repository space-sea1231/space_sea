#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <cmath>
#define __Debug

using namespace std;
typedef long long ll;

const int M = 1e3 +10;

int n, m, o;
int sss;

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

namespace Pts1 {
    const int N = 5e5 + 10;
    const int K = 8e2 + 10;
    int a[N];
    int L[K], R[K];
    int belong[N];
    int sum[K][M];
    int tot[M];

    void Query(int l, int r) {
        if (belong[l] < belong[r] - 1) {
            for (int i = 1; i <= M - 10; i++) {
                tot[i] = sum[belong[r] - 1][i] - sum[belong[l]][i];
                // sss += tot[i] * i;
            }
        }
        else memset(tot, 0, sizeof(tot));
        if (belong[l] == belong[r]) {
            for (int i = l; i <= r; i++) {
                tot[a[i]]++;
                // sss += a[i];
            }
        }
        else {
            for (int i = l; i <= R[belong[l]]; i++) tot[a[i]]++;// sss += a[i];
            for (int i = L[belong[r]]; i <= r; i++) tot[a[i]]++;// sss += a[i];
        }
    }
}

void Solve1() {
    using namespace Pts1;
    for (int i = 1; i <= m; i++) read(a[i]);
    int siz = sqrt(m);
    for (int i = 1; i <= siz; i++) {
        L[i] = (i - 1) * siz + 1;
        R[i] = i * siz;
    }
    if (R[siz] != m) {
        L[++siz] = R[siz] + 1;
        R[siz] = m;
    }
    for (int i = 1; i <= siz; i++) {
        // printf("L[%d]=%d R[%d]=%d\n", i, L[i], i, R[i]);
        for (int j = 1; j <= M - 10; j++) sum[i][j] = sum[i - 1][j];
        for (int j = L[i]; j <= R[i]; j++) {
            sum[i][a[j]]++;
            belong[j] = i;
        }
    }
    int l, r, tmp, h, ans;
    for (int i = 1; i <= o; i++) {
        ans = 0;
        read(tmp, l, tmp, r, h);
        Query(l, r);
        // printf("%d\n", sss);
        for (int j = M - 10; j >= 1; j--) {
            h -= tot[j] * j;
            ans += tot[j];
            if (h <= 0) {
                ans -= (-h) / j;
                break;
            }
        }
        if (h <= 0) printf("%d\n", ans);
        else printf("Poor QLW\n");
    }
}

namespace Pts2 {
    const int N = 2e2 + 10;
    int sum[N][N][M];
}

void Solve2() {
    using namespace Pts2;
    int a;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            read(a);
            sum[i][j][a] = 1;
            for (int k = 1; k <= M - 10; k++) {
                sum[i][j][k] += sum[i - 1][j][k] + sum[i][j - 1][k] - sum[i - 1][j - 1][k];
            }
        }
    }
    int sx, sy, fx, fy, h;
    int cnt, ans = 0;
    for (int i = 1; i <= o; i++) {
        ans = 0;
        read(sx, sy, fx, fy, h);
        for (int j = M - 10; j >= 1; j--) {
            cnt = sum[fx][fy][j] - sum[sx - 1][fy][j] - sum[fx][sy - 1][j] + sum[sx - 1][sy - 1][j];
            h -= cnt * j;
            ans += cnt;
            if (h <= 0) {
                ans -= (-h) / j;
                break;
            }
        }
        if (h <= 0) printf("%d\n", ans);
        else printf("Poor QLW\n");
    }
}

signed main() {
    // cin.tie(nullptr) -> ios::sync_with_stdio(false);
    read(n, m, o);
    if (n == 1) Solve1();
    else Solve2();
    return 0;
}