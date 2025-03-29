#include<bits/stdc++.h>
#define int long long
using namespace std;
int q,n,now[1000005];
int a[1000005];
string str;
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*f;
}
signed main(){
	freopen("shi.in","r",stdin);
	freopen("shi.out","w",stdout);
	q=read();
	while(q--){
		cin>>str;
		n=str.size();
		str=" "+str;
		int sum=0;
		for(int i=1;i<=n;i++) a[i]=str[i]-'0';
		if(n<=2){
			printf("0 0\n");
			continue;
		}
		for(int i=1;i<=n;i++) sum+=a[i];
		printf("\n");
		if(!sum){
			if(n&1) printf("%lld 0\n",n/2+1);
			else printf("%lld 0\n",n/2);
			for(int i=1;i<n;i+=2) printf("%lld ",i); 
			printf("\n");
			continue;
		} 
	}
	return 0;
}
