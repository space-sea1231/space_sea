#include<bits/stdc++.h>
#define int unsigned int
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
const int N=4e5+10;
const int inf=0xffffffff;
const int MOD=1e9+7;
int T,n,a[N];
signed main(){
    freopen("wei.in","r",stdin);
    freopen("wei.out","w",stdout);
    read(T);
    while(T--){
        read(n);
        int ans=0;
        for(int i=1;i<=n;i++) read(a[i]);
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                swap(a[i],a[j]);
                int res=0,nw=0;
                for(int k=1;k<=n;k++){
                    if(a[k]>a[k-1]) nw++;
                    else res+=nw*(nw+1)/2,nw=1;
                }
                res+=nw*(nw+1)/2;
                ans=max(ans,res);
                swap(a[i],a[j]);
            }
        }
        prt(ans);pc('\n');
    }
    return 0;
}