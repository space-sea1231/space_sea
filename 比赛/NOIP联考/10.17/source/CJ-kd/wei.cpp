#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N=4e5+5;
int n,a[N];
inline int read(){
    register int x=0,t=0;
    static char ch=getchar();
    while(!isdigit(ch)) t|=(ch=='-'),ch=getchar();
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return t?-x:x;
}
inline void work(){
	n=read();
	for(register int i=1;i<=n;i++){
		a[i]=read();
	}
	// if(n<=300){
		int ans=0;
		for(register int i=1;i<=n;i++){
			for(register int j=1;j<=n;j++){
				swap(a[i],a[j]);
				int tmp=0;
				for(register int k=1;k<=n;k++){
					int last=k;
					while(k+1<=n&&a[k+1]>a[k]) k++;
					tmp+=(k-last+1)*(k-last+2)/2;
				}
				swap(a[i],a[j]);
				ans=max(ans,tmp);
			}
		}
		printf("%lld\n",ans%(1ll<<32));
	// }
}
signed main(){
	freopen("wei.in","r",stdin);
	freopen("wei.out","w",stdout);
	int T=read();
	while(T--) work();
	return 0;
}
/*
1
6 7
1 -2 -1 0 -1 0
1 0 -2 -2 1 -1
-1 0 -1 -1 1 0
-1 -1 -1 0 -1 1
0 2 -1 1 2 -2
-1 0 -1 -1 -1 2
0 2 2 -1 0 -1
1 1 0 0 1 0 1
*/