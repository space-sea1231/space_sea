#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
using namespace std;
const int N=400010;
int T,n,a[N],sum[N];
bool flag[N];
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
int solve(){
//	for(int i=1;i<=n;i++)cout<<a[i]<<" ";
	int ans=0;
	for(int i=1;i<=n;i++){
		int j=i;
		while(a[j+1]>a[j])j++;
		ans+=sum[j-i+1];
//		cout<<"sum["<<j-i+1<<"]\n";
//		cout<<i<<" "<<j<<'\n';
		i=j;
	} 
//	cout<<'\n'<<ans<<'\n';
	return ans;
}
signed main(){
	freopen("wei.in","r",stdin);
	freopen("wei.out","w",stdout);
	T=read();
	for(int i=1;i<=N-10;i++){
		sum[i]=sum[i-1]+i;
	}
	while(T--){
		n=read();
		memset(a,0,sizeof a);
		for(int i=1;i<=n;i++)a[i]=read();
		memset(flag,0,sizeof flag);
		for(int i=1;i<=n;i++){
			int j=i;
			while(a[j+1]>a[j])j++;
			if(j-i+1>=3)for(int k=i+1;k<=j-1;k++)flag[k]=1;
//			cout<<i<<" "<<j<<'\n';
			i=j;
		} 
		int co=solve();
		for(int i=1;i<=n;i++){
//			if(flag[i]==1)continue;
			for(int j=i+1;j<=n;j++){
				swap(a[i],a[j]);
				co=max(co,solve());
				swap(a[i],a[j]); 
			} 
		}
		cout<<co<<'\n';
	} 
	return 0;
}
/*
T3
我猜测思路是在原序列中找到一个只修改一个位置的值可以得到的
最长连续子段，然后把它修改了
靠，没有时间了，暴力枚举罢 
O(n^2)枚举，O(n)check 
一个小优化是对于一段上升序列里面的数你肯定不用交换 
*/
