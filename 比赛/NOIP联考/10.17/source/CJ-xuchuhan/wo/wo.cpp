#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e6+5,mod=998244353;
int T,n;
int a[N],p1[N],p2[N],fac[N],power[N];
void init(){
	fac[0]=1,power[0]=1;
	for(int i=1;i<=1e6;i++)fac[i]=fac[i-1]*i%mod;
	for(int i=1;i<=1e6;i++)power[i]=power[i-1]*2%mod;
	return;
}
bool check(int x,int y){if((a[x]&&a[y])&&(a[x]>n&&a[y]>n||a[x]<=n&&a[y]<=n))return 1;return 0;}
void work(){
	cin>>n;
	for(int i=1;i<=2*n;i++)cin>>a[i];
	int sp=0;
	for(int i=1;i<=n;i++)
		if(check(i*2-1,i*2))sp++;
	int mid=n-sp,ans1=0,ans2=0,ans3=0,ans=1;
	for(int i=1;i<=n;i++){
		int c1=a[i*2-1],c2=a[i*2];
		if(c1&&c2)continue;
		else if(!c1&&!c2)ans1++,ans2++,ans3++;
		else{
			if(!c2)swap(c1,c2);
			if(c2<=mid)ans2++;
			else ans1++;
		}
	}
	ans=fac[ans1]*fac[ans2]%mod*power[ans3]%mod;
	cout<<ans<<"\n";
	return;
}
signed main(){
	freopen("wo.in","r",stdin);
	freopen("wo.out","w",stdout);
	cin>>T;init();
	while(T--)work();
	return 0;
}
