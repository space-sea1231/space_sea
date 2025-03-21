#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5,mod=998244353;
int a[N];
//int ans[N*13],ans1[N*13];
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
	freopen("wei.in","r",stdin);
	freopen("wei.out","w",stdout);
	int T=read();
	while(T--){
		int res=0,jli,jlj;
		int n=read();
		for(int i=1;i<=n;i++) a[i]=read();
		for(int i=1;i<=n;i++){
			for(int j=i+1;j<=n;j++){
				int ans=0;
				swap(a[i],a[j]);
				for(int k=1;k<=n;k++){
					int num=1;
					while(a[k+1]>=a[k]) num++,k++;
//					cout<<k<<endl;
					ans=ans+(num+1)*num/2%mod;
				}
				if(ans>res) jli=i,jlj=j,res=ans;;
				swap(a[i],a[j]);
			}
		}
		printf("%lld\n",res);
//		if(((a[jli]>a[jli-1]&&a[jli]<a[jli+1]&&(!a[jli]>a[jlj-1]&&!a[jli]<a[jlj+1]))||(a[jlj]<a[jlj+1]&&a[jlj]>a[jlj-1]&&(!a[jlj]>a[jli-1]&&!a[jlj]<a[jli+1])))) cout<<" "<<a[jli]<<" "<<a[jlj]<<endl<<endl;
	}
	return 0;
}
