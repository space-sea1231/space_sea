#include <bits/stdc++.h>
using namespace std;
#define int long long

inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch<='9'&&ch>='0')x=x*10+ch-'0',ch=getchar();
	return x*f;
}

void file(){
    freopen("wei.in","r",stdin);
    freopen("wei.out","w",stdout);
}

int ksm(int a,int b){
    int ans=1;
    while(b){
        if(b&1) ans=ans*a;
        a=a*a;
        b/=2;
    }
    return ans;
}

const int N=4e5+10;
int T,n,mod,a[N];

void solve(){
    n=read();
    for(int i=1;i<=n;i++)
        a[i]=read();
    int ans=0,maxx=0;
    a[0]=0;
    for(int i=1;i<=n;i++){
        for(int k=i;k<=n;k++){
            int now=a[i],now1=a[k];
            ans=0;
            swap(a[i],a[k]);
            int len=1,lst=1;
            for(int j=1;j<=n;j++){
                len=1;
                for(int w=j+1;w<=n;w++)
                    if(a[w]>a[w-1]) len++;
                    else break;
                ans+=len;
            }
            a[i]=now,a[k]=now1;
            maxx=max(maxx,ans);
        }
    }
    cout<<maxx%mod<<"\n";
}
signed main(){
    file();
    mod=ksm(2,32);
    T=read();
    while(T--)
        solve();
    return 0;
}