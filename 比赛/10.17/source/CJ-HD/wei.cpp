#include<bits/stdc++.h>
#define int long long
using namespace std;
const int M=4e5+5;
const int mod=(1ll<<32);
int t,m,n,a[M],q[M],t1,p[M],t2;
int ans,cnt;
int c[M];
void pushin(int x,int v){
	while(x<=n){
		c[x]+=v;
		x+=(x&-x);
	}
}
int getsum(int x){
	int sum=0;
	while(x){
		sum+=c[x];
		x-=x&-x;
	}
	return sum;
}
void sol(){
	int sum=0,cnt2=0;
	memset(c,0,sizeof(c));
	for(int i=1;i<=n;i++){
		if(a[i-1]>a[i]||i==1){
			pushin(a[i],1);
			sum++;
			continue;
		}
		if(a[i-1]==1){
			pushin(a[i],2);
			sum+=2;
			continue;
		}
		int x=getsum(a[i-1])-getsum(a[i-1]-1)+1;
		pushin(a[i],x);
		sum+=x;
	}
	if(sum>ans)ans=sum;
}
signed main(){
	freopen("wei.in","r",stdin);
	freopen("wei.out","w",stdout);
	cin>>t;
	while(t--){
		cin>>n;
		ans=cnt=0;
		for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
		t1=t2=0;
		for(int i=1;i<=n;i++){
			if(t1==0||a[q[t1]]<a[i])q[++t1]=i;
		}
		for(int i=n;i>=1;i--){
			if(t2==0||a[p[t2]]>a[i])p[++t2]=i;
		}
		for(int i=1;i<=t1;i++){
			for(int j=1;j<=t2;j++){
				swap(a[q[i]],a[p[j]]);
				sol();
				swap(a[q[i]],a[p[j]]);
			}
		}
		cout<<ans%mod<<"\n";
	}
	return 0;
}
