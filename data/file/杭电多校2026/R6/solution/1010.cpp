#include<bits/stdc++.h>
using namespace std;
#define fi first
#define sc second
#define pii pair<int,int>
#define pdd pair<double,double>
#define pb push_back
#define umap unordered_map
#define mset multiset
#define pq priority_queue
#define ull unsigned long long
#define i128 __int128
#define ld long double
#define fixs fixed<<setprecision
#define FileIn(x) freopen(x".in","r",stdin)
#define FileOut(x) freopen(x".out","w",stdout)
#define FileIO(x) FileIn(x),FileOut(x);
namespace FastIO{
    char buf[1<<21],*p1=buf,*p2=buf;
#define getchar() (p1==p2&&(p1=buf,p2=(p1+fread(buf,1,1<<21,stdin)))==p1?EOF:*p1++)
    template<typename T>inline T read(){T x=0,w=0;char ch=getchar();while(ch<'0'||ch>'9') w|=(ch=='-'),ch=getchar();while('0'<=ch&&ch<='9') x=x*10+(ch^'0'),ch=getchar();return w?-x:x;}
    template<typename T>inline void write(T x){if(!x) return;write<T>(x/10),putchar((x%10)^'0');}
    template<typename T>inline void print(T x){if(x>0) write<T>(x);else if(x<0) putchar('-'),write<T>(-x);else putchar('0');}
    template<typename T>inline void print(T x,char en){print<T>(x),putchar(en);}
    inline string read(){char c=getchar();while(c==' '||c=='\n'||c=='\r') c=getchar();string str;while(c!=' '&&c!='\n'&&c!='\r'&&c!=EOF) str+=c,c=getchar();return str;}
};using namespace FastIO;
i128 n,m;
i128 calc(i128 x,i128 y){
    i128 k=x/(y+1);
    return (x*x-(2*k+1)*x+k*(k+1)*(y+1))/2;
}
void solve(){
    n=read<i128>(),m=read<i128>(),print(calc(n+m,m),'\n');
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int t=read<int>();
    while(t--) solve();
    return 0;
}
/*
Samples
input:

output:

THINGS TODO:
检查freopen，尤其是后缀名
检查空间
检查调试语句是否全部注释
*/
