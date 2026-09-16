#include<bits/stdc++.h>
using namespace std;
namespace FastIO{
    const int BUF_L=1<<23;
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
    void flush(){
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
        while(ch==' '||ch=='\n'||ch=='\r'){
            ch=getchar();
        }
        while(ch!=' '&&ch!='\n'&&ch!='\r'&&ch!=EOF){
            res+=ch;
            ch=getchar();
        }
    }
    template<> void read(char &res){
        char ch=getchar();
        res=' ';
        while(ch==' '||ch=='\n'||ch=='\r'){
            ch=getchar();
        }
        res=ch;
    }
    void read(char *c){
        int ip=0;
        char ch=getchar();
        while(ch==' '||ch=='\n'||ch=='\r'){
            ch=getchar();
        }
        while(ch!=' '&&ch!='\n'&&ch!='\r'&&ch!=EOF){
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
        typename make_unsigned<T>::type tmp;
        if(tp<0){
            putchar('-');
            tmp=-(typename make_unsigned<T>::type)tp;
        }
        else{
            tmp=tp;
        }
        if(tmp==0){
            putchar('0');
            return ;
        }
        static char buf[32];
        int idx=0;
        while(tmp){
            buf[idx++]=tmp%10+'0';
            tmp/=10;
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
    template<typename T,typename... Arg>void write(const T& v1,const Arg&... args){
        write(v1);
        write(args...);
    }
    template<typename... Arg>void write(const Arg&... args){
        initializer_list<int>{(write(args),0)...,0};
    }
}
using FastIO::read;
using FastIO::write;
int n,q,root;
vector<int> to[2000006],nto[1000006],cont[2000006];
int dfn[2000006],siz[2000006];
bool vis[2000006];
void DFS(int now){
    static int mdfn=0;
    dfn[now]=++mdfn;
    siz[now]=1;
    if(now<=n){
        cont[now].push_back(now);
        return ;
    }
    int ts;
    for(int v:to[now]){
        DFS(v);
        siz[now]+=siz[v];
        if(dfn[v]<=dfn[now-n]&&dfn[now-n]<=dfn[v]+siz[v]) ts=v;
    }
    if(dfn[now]<dfn[now-n]&&dfn[now-n]<dfn[now]+siz[now]){
        for(int v:to[now]){
            if(v==ts) continue;
            for(int w:cont[v]){
                nto[now-n].push_back(w);
                vis[w]=1;
            }
            cont[v].clear();
        }
        swap(cont[now],cont[ts]);
    }
    else{
        for(int v:to[now]){
            if(cont[now].size()<cont[v].size()) swap(cont[now],cont[v]);
            for(int i:cont[v]){
                cont[now].push_back(i);
            }
            cont[v].clear();
        }
    }
}
void DFS2(int now){
    static int mdfn=0;
    dfn[now]=++mdfn;
    siz[now]=1;
    for(int v:nto[now]){
        // printf("%d %d\n",now,v);
        DFS2(v);
        siz[now]+=siz[v];
    }
}
bool Chk(int x,int y){
    return dfn[x]<dfn[y]&&dfn[y]<dfn[x]+siz[x]||dfn[y]<dfn[x]&&dfn[x]<dfn[y]+siz[y];
}
void Work(){
    read(n,q);
    for(int i=1;i<=n*2;i++){
        int f;
        read(f);
        if(f==0) root=i;
        else to[f].push_back(i);
    }
    DFS(root);
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            DFS2(i);
        }
    }
    for(int i=1;i<=q;i++){
        int a,b;
        read(a,b);
        write(a==b||Chk(a,b)?"Yes\n":"No\n");
    }
}
signed main(){
    // freopen("umbrella/12.in","r",stdin);
    // freopen("test.out","w",stdout);
    atexit(FastIO::flush);
    int t=1;
    // read(t);
    while(t--){
        Work();
    }
    return 0;
}
/*

*/