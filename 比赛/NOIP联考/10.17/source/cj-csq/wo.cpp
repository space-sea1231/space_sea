#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1000010,mod=998244353;
int T,n,p[N];
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
int quick_pow(int a,int b){
	int ans=1;
	while(b>0){
		if(b%2==0)(a*=a)%=mod,b/=2;
		else (ans*=a)%=mod,b--;
	}
	return ans;
}
signed main(){
	freopen("wo.in","r",stdin);
	freopen("wo.out","w",stdout);
	T=read();
	while(T--){
		n=read();
		double mid=n+0.5;
		int cntmax=n,cntmin=n,ans=1,num=0,temp=0,temp1=0;
		for(int i=1;i<=2*n;i++){
			p[i]=read();
			if(p[i]==0)continue;
			if(p[i]>ss)cntss--;
			if(p[i]>mid)cntmax--;
			else cntmin--; 
		}
//		cout<<cntmax<<" "<<cntmin<<'\n';
		for(int i=1;i<=2*n;i+=2){
			num=0;
			if(p[i]==0&&p[i+1]!=0)num=p[i+1];
			else if(p[i]!=0&&p[i+1]==0)num=p[i];
			if(num==0)continue;
//			cout<<i<<" "<<i+1<<":"<<num<<'\n';
			if(num>mid){
				(ans*=cntmin)%=mod;
				cntmin--;
			}
			else if(num<mid){
				(ans*=cntmax)%=mod;
				cntmax--;
			}
//			cout<<ans<<'\n';
		}
		for(int i=1;i<=2*n;i+=2){
			if(p[i]==0&&p[i+1]==0){
				temp1++;
				if(cntmax>0&&cntmin>0){
					(ans*=cntmax)%=mod;
					(ans*=cntmin)%=mod;
					cntmax--,cntmin--;
					temp++;
				}
				else if(cntmax>0&&cntmin==0){
					(ans*=cntmax)%=mod;
					(ans*=(cntmax-1))%=mod;
					cntmax--,cntmax--;
//					temp++;
				}
				else if(cntmin>0&&cntmax==0){
					(ans*=cntmin)%=mod;
					(ans*=(cntmin-1))%=mod;
					cntmin--,cntmin--;
//					temp++;
				}
//				cout<<i<<" "<<i+1<<":"<<cntmax<<" "<<cntmin<<" "<<ans<<'\n';
			}
		}
		ans=ans*quick_pow(2,temp)%mod;
//		cout<<ans<<' '<<temp1<<"\n";
//		for(int i=temp1;i>=1;i--)(ans*=i)%=mod;
		cout<<ans<<'\n';
	}
	return 0;
}
/*
T1
这题怎么看起来这么眼熟呢
结合数据范围我们先猜这是一个贪心 
我猜测应该是先把它填了数的那些组填完
剩下的数字只要 >mid的和 <mid的一一匹配就肯定最优。
发现那些有限制的也是这么填最优的 
en有一点情况没有讨论到，但是居然过了大样例二 
继续讨论一下 
*/
