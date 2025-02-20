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
    freopen("ge.in","r",stdin);
    freopen("ge.out","w",stdout);
}

const int N=25;
int T,n,m,b[N*N];

struct nd{
    int x,id;
    bool operator<(const nd&i)const{
        return x<i.x;
    }
}a[N];

void solve(){
    n=read(),m=read();
    if(n==1){
        for(int j=1;j<=m;j++)
            a[j].x=read(),a[j].id=j;
        for(int i=1;i<=m;i++)
            b[i]=read();
        sort(a+1,a+m+1);
        int ans=0,minn=1e18;
        ans=a[m].x-a[1].x;  
        for(int i=1;i<=m;i++){
            if(b[a[i].id]==0) continue;
            int ans1=a[i].x-a[1].x+ans;
            int ans2=a[m].x-a[1].x+ans;
            minn=min(minn,min(ans1,ans2));
        }
        cout<<minn<<" "<<"1 ";
        return ;
    }
    cout<<"NIE\n";
    return ;
}
signed main(){
    file();
    T=read();
    while(T--)
        solve();
    return 0;
}