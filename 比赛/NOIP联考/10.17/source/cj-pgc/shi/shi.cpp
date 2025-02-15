#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5,mod=998244353;
char a[N],aa[N];
int ans[N*13],ans1[N*13];
inline int read(){
	int a=1,b=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') a=-a;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		b=(b<<1)+(b<<3)+(ch^48);
		ch=getchar();
	}
	return a*b; 
}


signed main(){
	freopen("shi.in","r",stdin);
	freopen("shi.out","w",stdout);
	int T=read();
	while(T--){
		int cntn=0,pan=0,cntn1=0,pan1=0;
		scanf("%s",aa+1);
		
		int n=strlen(aa+1);
		for(int i=1;i<=n;i++) a[i]=aa[i];
		
		for(int i=2;i<=n-2;i++){
			while(a[i-1]=='1'&&i<=n) i++;
			if(i>n) break;
			if(a[i]=='1'){
				a[i]='0';
				if(a[i+1]=='0'&&a[i+2]=='0') a[i+2]=='1';
				else a[i+2]=='0';
				ans[++cntn]=i+1;
			} 
			if(a[i+1]=='0') a[i+1]='1';
			else a[i+1]='0';
			a[i-1]='1';
			ans[++cntn]=i;
		}
		if(a[n-1]=='0'&&a[n]=='0') ans[++cntn]=n-1,pan=1;
		if(a[n-1]=='1'&&a[n]=='1') pan=1;
//		for(int i=1;i<=n;i++) cout<<a[i]<<" ";cout<<endl;
		for(int i=1;i<=n;i++) a[i]=aa[i];
		for(int i=n-1;i>=2;i--){
			while(a[i+1]=='1'&&i>=1) i--;
			if(i<1) break;
			if(a[i]=='1'){
				a[i]='0';
				if(a[i-1]=='0'&&a[i-2]=='0') a[i-2]=='1';
				else a[i-2]=='0';
				ans1[++cntn1]=i-1;
			} 
			if(a[i-1]=='0') a[i-1]='1';
			else a[i-1]='0';
			a[i+1]='1';
			ans1[++cntn1]=i;
		}
		if(a[2]=='0'&&a[1]=='0') ans1[++cntn]=2,pan1=1;
		if(a[2]=='1'&&a[1]=='1') pan1=1;
//		cout<<pan<<" "<<pan1<<endl;
		if(pan>pan1){
//			cout<<1<<endl;
			printf("%lld %lld\n",(pan==1?n-1:n-2),cntn);
			for(int i=1;i<=cntn;i++) printf("%lld ",ans[i]);
			puts("");
		}
		else{
//	for(int i=1;i<=n;i++) cout<<a[i]<<" ";cout<<endl;
				printf("%lld %lld\n",(pan1==1?n-1:n-2),cntn1);
				for(int i=1;i<=cntn1;i++) printf("%lld ",ans1[i]);
				puts("");
		}
	}
	return 0;
}
