/*
超级大样例
抽象题目名
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define flush() fwrite(obuf,1,O-obuf,stdout)
#define putchar(x) ((O==obuf+(1<<21))&&(flush(),O=obuf)),*O++=x
char buf[1<<23],*p1=buf,*p2=buf,obuf[1<<23],*O=obuf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline int read() {
	register int x=0,f=1;register char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
	return x*f;
}
inline void write(register int x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar((x%10)^48);
}
struct Flush{
    ~Flush(){flush();}
}_;
#define N 2000010
const int p=998244353;
int t,n,a[N],A[N],BAS[N];
bool vis[N],f[N],id[N];
signed main(){
    freopen("wo.in","r",stdin);
    freopen("wo.out","w",stdout);
    A[0]=1;
    BAS[0]=1;
    for(int i=1;i<=2000000;i++){
        A[i]=A[i-1]*i%p;
        BAS[i]=BAS[i-1]*2%p;
    }
    t=read();
    while(t--){
        n=read();
        int bas=0,mid,smx=n,smn=n,sum=0,pos,ss=2*n;
        for(int i=1;i<=2*n;i++){
            vis[i]=0;
            f[i]=0;
            id[i]=0;
        }
        for(int i=1;i<=2*n;i++){
            a[i]=read();
            if(a[i]){
                vis[i]=1;
                id[a[i]]=1;
            }
        }
        for(int i=1;i<=n;i++){
            if(vis[2*i]&&vis[2*i-1]){
                ss-=2;
                f[a[2*i]]=1;
                f[a[2*i-1]]=1;
            }
            else{
                if((!vis[2*i])&&(!vis[2*i-1])){
                    bas++;
                }
            }
        }
        // cout<<ss<<endl;
        smx=smn=ss/2;
        for(int i=1;i<=2*n;i++){
            if(!f[i]){
                sum++;
                if(sum<=(ss/2)){
                    if(id[i]){
                        smn--;
                    }
                    if(sum==smx){
                        pos=i;
                        break;
                    }
                }
            }
        }
        for(int i=pos+1;i<=2*n;i++){
            if(!f[i]){
                if(id[i]){
                    smx--;
                }
            }
        }
        // cout<<smx<<' '<<smn<<' '<<bas<<endl;
        cout<<A[smx]*A[smn]%p*BAS[bas]%p<<endl;
    }
    return 0;
}