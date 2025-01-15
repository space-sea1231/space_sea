#include<bits/stdc++.h>
#define int long long
#define inf 0x3f3f3f3f
using namespace std;
const int mod=998244353,N=1000010;
int T,n,a[N];
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-'0';
		c=getchar();
	}
	return x*f;
} 
signed main(){
	freopen("shi.in","r",stdin);
	freopen("shi.out","w",stdout);
	T=read();
	while(T--){
		n=read();
		char a;
		bool flag=0;
		for(int i=1;i<=n;i++){
			cin>>a;
			if(a!='1')flag=1;
		}
		if(flag==0)cout<<n<<'\n';
		else cout<<n-1<<'\n';
	}
	return 0;
}
