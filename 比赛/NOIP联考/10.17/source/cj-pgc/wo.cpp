#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5,mod=998244353;
int f2[N],jc[N],num[N],a[N],num1[N];

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
	freopen("wo.in","r",stdin);
	freopen("wo.out","w",stdout);
	int T=read();
	f2[0]=1,jc[0]=1;
	for(int i=1;i<=1000005;i++) f2[i]=f2[i-1]*2%mod;
	for(int i=1;i<=1000005;i++) jc[i]=jc[i-1]*i%mod;
	while(T--){
		int n=read();
		int sum1=0,sum2=0,sum=0,sum3=0;
		for(int i=1;i<=2*n;i++) num[i]=num1[i]=0;
		for(int i=1;i<=n;i++){
			a[i*2-1]=read();
			a[i*2]=read();
			if(a[i*2-1]!=0&&a[i*2]!=0) num[a[i*2-1]]=num[a[i*2]]=1,sum+=2;
			if(a[i*2-1]!=0) num1[a[i*2-1]]=1;
			if(a[i*2]!=0) num1[a[i*2]]=1;
			if(a[i*2-1]==0&&a[i*2]==0) sum3++;
		}
		int id=0,mid;
		for(int i=1;i<=2*n;i++){
			if(!num[i]) id++;
			if(id==n-sum/2){
				mid=i;
				break;
			}
		}
//		cout<<mid<<endl;
		int ans=f2[sum3];
		for(int i=1;i<=mid;i++){
			if(!num1[i]) sum1++; 
		}
		for(int i=mid+1;i<=2*n;i++){
			if(!num1[i]) sum2++;
		}
//		cout<<sum1<<" "<<sum2<<endl;
		ans=(ans*jc[sum1]%mod*jc[sum2]%mod);
//		ans%=mod;
		printf("%lld\n",ans);
	}
	return 0;
}
