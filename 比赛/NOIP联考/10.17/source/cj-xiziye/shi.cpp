#include<bits/stdc++.h>
#define int long long
#define pc putchar
using namespace std;
void read(int &p){
    int res=0,fh=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') fh=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') res=res*10+ch-'0',ch=getchar();
    p=res*fh;
}
void prt(int x){
    if(x<0) putchar('-'),x=-x;
    if(x>=10) prt(x/10);
    putchar(x%10+'0');
}
const int N=3e6+10;
const int inf=0x7fffffffffffffff;
const int MOD=1e9+7;
int T,n,a[N],cg[5*N];
char s[N];
signed main(){
    // freopen("shi.in","r",stdin);
    // freopen("shi.out","w",stdout);
    read(T);
    while(T--){
        scanf("%s",s+1);
        int flag=0;
        n=strlen(s+1);
        for(int i=1;i<=n;i++) a[i]=s[i]-'0';
        for(int i=1;i<=n;i++) if(a[i]==0) flag++;
        // if(flag==0){prt(n);printf(" 0\n\n");continue;}
        // if(flag==1){prt(n-1);printf(" 0\n\n");continue;}
        // if(n==2){prt(2-flag);printf(" 0\n\n");continue;}
        // if(n==3){
        //     if(flag==2){prt(1);printf(" 0\n\n");continue;}
        //     if(flag==3){prt(2);printf(" 0\n\n");continue;}
        // }
        int cnt=0;
        for(int i=1;i<=n-2;i++){
            if(a[i]==1) continue;
            if(a[i+1]==0){
                a[i]=1;
                a[i+2]^=1;
                cg[++cnt]=i+1;
            }
            else{
                cg[++cnt]=i+2;
                cg[++cnt]=i+1;
                if(a[i+2]==0){
                    a[i+1]=0;
                    a[i+3]^=1;
                }
                else{
                    a[i+1]=0;
                    a[i+3]=0;
                }
                a[i]=1;
                a[i+2]^=1;
            }
        }
        if(a[n]==0&&a[n-1]==0&&a[n-2]==0&&n-2>0){
            cg[++cnt]=n-1;
            a[n]^=1;
            a[n-1]^=1;
            a[n-2]^=1;
        }
        int res=0;
        // for(int i=1;i<=n;i++) prt(a[i]),pc(' ');pc('\n');
        for(int i=1;i<=n;i++) res+=a[i];
        prt(res);pc(' ');prt(cnt);pc('\n');
        for(int i=1;i<=cnt;i++) prt(cg[i]),pc(' ');pc('\n');
    }
    return 0;
}