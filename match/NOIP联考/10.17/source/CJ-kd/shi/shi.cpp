#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N=1e6+5;
int n,sum[N];
char s[N];
inline int read(){
    register int x=0,t=0;
    static char ch=getchar();
    while(!isdigit(ch)) t|=(ch=='-'),ch=getchar();
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    return t?-x:x;
}
inline void work(){
	cin>>(s+1);
	n=strlen(s+1);
	sum[n+1]=0;
	for(register int i=n;i>=1;i--) sum[i]=sum[i+1]+(s[i]=='1');
	if(n<=2){
		printf("%lld %lld\n\n",sum[1],0ll);
		return;
	}
	if(n==3){
		if(sum[1]==0) printf("2 1\n2\n");
		else printf("%lld 0\n\n",sum[1]);
		return;
	}
	if(n==4){
		printf("%lld 0\n\n",sum[1]);
		return;
	}
	printf("%lld 0\n\n",n-1);
}
signed main(){
	freopen("shi.in","r",stdin);
	freopen("shi.out","w",stdout);
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int T;cin>>T;
	while(T--) work();
	return 0;
}