#include <bits/stdc++.h>
using namespace std;
namespace IO{
    const int BUF=1<<21;
    char buff[BUF],*p1=buff,*p2=buff;
    #define gc() (p1==p2&&(p2=((p1=buff)+fread(buff,1,BUF,stdin)),p1==p2)?EOF:*p1++)
    template<typename T>inline void read(T &x){
        char ch=gc();x=0;int f=1;
        while(!isdigit(ch)){if(ch=='-')f=-1;ch=gc();}
        while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=gc();
        x*=f;
    }
    char obuf[BUF],*p3=obuf;
    inline void pc(char ch){
        if(p3-obuf<BUF) *p3++=ch;
        else fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=ch;
    }
    inline void put(const char *s){while(*s) pc(*s),++s;}
    char ch[64];int ctop;
    template<typename T>inline void print(T x){
    	if(x<0) x=~x+1,pc('-');
        if(!x) return pc(48);
        while(x) ch[++ctop]=x%10^48,x/=10;
        while(ctop) pc(ch[ctop--]);
    }
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);p3=obuf;}
}
using namespace IO;
signed main()
{
	int n;
	read(n);
	print(n);
	flush();
}
