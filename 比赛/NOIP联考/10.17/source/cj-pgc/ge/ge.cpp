#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=305,mod=998442353;
int a[N],pan[N],num[N],num1[N],aa[N][N];
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
	freopen("ge.in","r",stdin);
	freopen("ge.out","w",stdout);
	int T=read();
	while(T--){
		
		int n=read(),m=read();
		if(n==1){
//			cout<<114514<<endl;
			int cntn=0;
			for(int i=1;i<=m;i++) a[i]=read(),num1[i]=a[i];
			for(int i=1;i<=m;i++) pan[i]=read();
			for(int i=1;i<=m;i++){
				if(pan[i]) num[++cntn]=a[i];
				
			}
			if(cntn==0){
				puts("NIE");
				continue;
			}
			
			sort(num+1,num+cntn+1);
			sort(num1+1,num1+m+1);
			
//			for(int i=1;i<=cntn;i++ ) cout<<num[i]<<" ";cout<<endl;
			if(num[1]-num1[1]==num1[m]-num[cntn]){
				printf("%lld 2\n",num[1]-num1[1]+num1[m]-num1[1]);
			}
			else{
				int tmp=min(num[1]-num1[1],num1[m]-num[cntn]);
//				cout<<tmp<<endl;
				printf("%lld 1\n",tmp+num1[m]-num1[1]);
			}
		}
		else 	if(m==2){
			int ans=1;
			int num=0;
			for(int i=1;i<=2;i++){
				for(int j=1;j<=n;j++) aa[i][j]=read();
			}
			for(int i=1;i<=m;i++) pan[i]=read();
			for(int i=1;i<=n;i++){
				ans=abs(aa[1][i]-aa[2][i])*ans%mod;
				num=(num+abs(aa[1][i]-aa[2][i]))%mod;
			} 
//			cout<<ans<<endl;
			if(pan[1]==1&&pan[2]==1) printf("%lld %lld\n",num,ans*2);
			else{
				if(pan[1]==0&&pan[2]==0) puts("NIE");
				else printf("%lld %lld\n",num,ans);
			}
		}
	}
	return 0;
}
