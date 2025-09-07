#include<bits/stdc++.h>
#define FAST true
#define FIO true
#define DEBUG false
using namespace std;
#if FIO
void fio(string s,int i=0){
    freopen(((s+(i?to_string(i):""))+".in").c_str(),"r",stdin);
    freopen(((s+(i?to_string(i):""))+".out").c_str(),"w",stdout);
}
#endif
#define int long long
//#define int unsigned int
//#define int __int128
#if DEBUG
bool Memory_start;
void debug();
#endif
#if FAST
inline int read(){
    char c=getchar();
    int ret=0,f=1;
    while(c<'0'||c>'9'){
        if(c=='-')f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        ret=(ret<<3)+(ret<<1)+c-'0';
        c=getchar();
    }return ret*f;
}
inline void write(int x,int op=0){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10,0);
    putchar((char)(x%10+'0'));
    if(op){
        if(op>0)puts("");
        if(op<0)putchar(' ');
        if(op==0)puts("114514");
    }
}
#endif
const int mod=1ll<<32;
int T;
int n;
signed main(){
    fio("wei");
    T=read();
    while(T--){
        n=read();
        for(int i=1;i<=n;i++)read();
        write(n*(n+1)/2%mod,1);
    }
#if DEBUG
    debug();
#endif
    return 0;
}
#if DEBUG
bool Memory_end;
void debug(){
    cerr<<"Time: "<<clock()<<" ms\n";
    cerr<<fixed<<setprecision(6)<<"Memory: "<<abs(&Memory_start-&Memory_end)/1024.0/1024.0<<" MB";
}
#endif