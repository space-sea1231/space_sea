#include<bits/stdc++.h>
using namespace std;
namespace FastIO{
    const int BUF_L=1<<20;
    char ibuf[BUF_L];
    char obuf[BUF_L];
    char *po=obuf;
    char *p1=ibuf,*p2=ibuf;
    inline char getchar(){
        return (p1==p2&&(p2=(p1=ibuf)+fread(ibuf,1,BUF_L,stdin),p1==p2))?EOF:*p1++;
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
        while(ch==' '||ch=='\n'||ch=='\r'&&ch!=EOF){
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
int n;
vector<int> to[100005];
int fa[100005];
int vis[100005];
vector<int> unp[100005];
int ans;
void DP(int now,int fa,int root){
    for(int v:to[now]){
        if(v!=fa){
            DP(v,now,root);
        }
    }
    if(!vis[now]&&!vis[fa]) vis[now]=vis[fa]=1,ans++;
    if(!vis[now]) unp[root].push_back(now);
}
int avil=0;
vector<int> id;
vector<int> st;
void Work(){
    read(n);
    vis[0]=1;
    for(int i=2;i<=n;i++){
        read(fa[i]);
        to[fa[i]].push_back(i);
    }
    for(int i=1;i<=n;i++){
        if(fa[i]==0){
            DP(i,0,i);
            id.push_back(i);
        }
    }
    sort(id.begin(),id.end(),[&](int a,int b)->bool{
        if(a==1) return 1;
        if(b==1) return 0;
        if(vis[a]!=vis[b]) return vis[a]>vis[b];
        return unp[a].size()>unp[b].size();
    });
    for(int i:unp[1]) st.push_back(i);
    for(int i=1;i<id.size();i++){
        if(!st.empty()&&!vis[id[i]]){
            vis[id[i]]=1;
            vis[st.back()]=1;
            fa[id[i]]=st.back();
            st.pop_back();
            ans++;
        }
        else{
            fa[id[i]]=1;
        }
        for(int v:unp[id[i]]){
            if(!vis[v]) st.push_back(v);
        }
    }
    write(ans,'\n');
    for(int i=2;i<=n;i++){
        write(fa[i],' ');
    }
}
signed main(){
    // freopen("tree.in","r",stdin);
    // freopen("tree.out","w",stdout);
    atexit(FastIO::flush);
    int t=1;
    // read(t);
    while(t--){
        Work();
    }
    return 0;
}