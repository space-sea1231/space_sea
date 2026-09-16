#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e6 + 10;

int T;
int n;
int a[N];
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

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    // freopen("dog.in", "r", stdin);
    // freopen("dog.out", "w", stdout);
    read(T);
    while (T--) {
        read(n); a[n + 1] = INF;
        bool flag = true;
        int cnt = 0;
        for (int i = 1; i <= n; i++) read(a[i]);
        for (int i = 1; i <= n; i++) {
            if (a[i] < a[i + 1]) {
                if (a[i] <= cnt) {flag = false; break;}
                cnt++;
            }
        }
        if (flag) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}//ABC208H