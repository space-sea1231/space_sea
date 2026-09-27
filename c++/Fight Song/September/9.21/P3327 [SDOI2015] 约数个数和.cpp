#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
// #define int long long
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 5e4 + 10;
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

int T, n, m;
int cnt;
int prime[N];
int mu[N], sum[N];
int f[N], g[N];
ll s[N];
bool vis[N];

void Prime() {
    mu[1] = 1;
    for (int i = 2; i < N; i++) {
        if (!vis[i]) {
            prime[++cnt] = i;
            mu[i] = -1;
        }
        for (int j = 1; j <= cnt && i * prime[j] < N; j++) {
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0) break;
            mu[i * prime[j]] = -mu[i]; 
        }
    }
    for (int i = 1; i < N; i++) sum[i] = sum[i - 1] + mu[i];
    for (int i = 1; i < N; i++) {
        for (int l = 1, r = 0; l <= i; l = r + 1) {
            r = (i / (i / l));
            s[i] += (ll)(i / l) * (r - l + 1);
        }
    }
}

ll Query() {
    ll ans = 0;
    for (int l = 1, r = 0; l <= n; l = r + 1) {
        r = min(n/(n/l), m/(m/l));
        ans += (ll)(sum[r] - sum[l - 1]) * s[n/l] * s[m/l];
    }
    return ans;
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    Prime();
    read(T);
    while (T--) {
        read(n, m);
        if (n > m) swap(n, m);
        printf("%lld\n", Query());
    }
    return 0;
}
/*
梦境是幻想的国度，当你愈发深入时，你便来到了梦境的源泉：梦核
梦境开始了
下雨的地铁站，爬山虎爬上了洁白的瓷砖墙壁。细雨朦胧，藤蔓覆盖了铁轨。
在微光和雨水弥漫出的雾气中，一切都显得这么不真实，但是又感到似曾相识，仿佛它们只存在于我的回忆当中
我与几位同学站在站台边，一道楼梯一路向上，通向地表
我们走上楼梯，来到地面。外面不是车水马龙，而是一片下着小雨的沼泽地
༺༒ 微 雨 森 林 ༒༻
几条林中走道衍伸出去，跨过一片片小水洼，消失在远方的森林中。雨水拍打在木板上，激起和弦乐章。
十几棵小树孤立于道路旁，水洼中，将眼前的景色染成了墨绿色，在迷雾中，那种不真实的感觉又来了。
我们最后互相看了一眼，没有一个人说话，走上了属于各自的走道
梦境结束了(－v－)
*/