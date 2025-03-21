#include <bits/stdc++.h>
using namespace std;
#define int long long
#define fr first
#define sc second
inline int read(){
    int res=0,f=1;char c=getchar();
    while (c<'0'||c>'9') {if (c=='-') f=-1;c=getchar();}
    while (c>='0'&&c<='9') {res=res*10+(c-'0');c=getchar();}
    return res*f;
}
const int N=1e6+5;
int T,n,a[N],mp[N<<2],ans,id;
int yf(int x,int y){
    return (x==0&&y==0);
}
void dfs(int lst,int op){
    int x=0;
    for (int i=1;i<=n;i++)
        x=(x<<1)+a[i];
    if (mp[x]) return;
    mp[x]=1;
    int popcnt=0;
    for (int i=1;i<=n;i++)
        popcnt+=a[i];
    if (popcnt>ans) ans=popcnt,id=x;
    for (int i=2;i<n;i++){
        int l=a[i-1],r=a[i+1];
        a[i-1]=yf(a[i-1],a[i]);
        a[i+1]=yf(a[i+1],a[i]);
        dfs(x,i);
        a[i-1]=l,a[i+1]=r;
    }
}
signed main(){
    freopen("shi.in","r",stdin);
    freopen("shi.out","w",stdout);
    T=read();
    while (T--){
        string s;
        cin>>s,n=s.size(),s=' '+s;
        if (n<=20){
            for (int i=0;i<(1ll<<n);i++)
                mp[i]=0;
            for (int i=1;i<=n;i++)
                a[i]=s[i]-'0';
            ans=0,dfs(0,0);
            cout<<ans<<' '<<0<<'\n';
        }
        else{
            bool sb=1;
            for (int i=1;i<=n;i++)
                sb&=(s[i]=='1');
            if (sb) cout<<n<<' '<<0<<'\n';
            else cout<<n-1<<' '<<0<<'\n';
        }
    }
    return 0;
}