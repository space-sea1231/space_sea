#include<bits/stdc++.h>
#define int int64_t
using namespace std;
const int mod=998244353;
int n=2e6,a[2000005],T,tp[2000005],c0,c1,cnt,fac[2000005],pw[2000005];
int chk(int x){
	return x>=mod?x-mod:x;
}
int32_t main(){
	freopen("wo.in","r",stdin),freopen("wo.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cin>>T,fac[0]=pw[0]=1;
	for(int i=1;i<=n;i++)
		fac[i]=fac[i-1]*i%mod,pw[i]=chk(pw[i-1]<<1);
	while(T--){
		cin>>n,cnt=n,c0=c1=0,tp[0]=-1;
		for(int i=1;i<=n<<1;i++)
			cin>>a[i],tp[i]=-1;
		for(int i=1;i<=n;i++)
			if(a[(i<<1)-1]&&a[i<<1])
				tp[min(a[(i<<1)-1],a[i<<1])]=0,tp[max(a[(i<<1)-1],a[i<<1])]=1,cnt--;
		for(int i=1;i<=n<<1;i++)
			if(!~tp[i]){
				if(cnt)
					tp[i]=0,cnt--;
				else
					tp[i]=1;
			}
		for(int i=1;i<=n;i++){
			if(tp[a[(i<<1)-1]]&&tp[a[i<<1]])
				c0++;
			if(tp[a[(i<<1)-1]]!=1&&tp[a[i<<1]]!=1)
				c1++;
			if(!a[(i<<1)-1]&&!a[i<<1])
				cnt++;
		}
		cout<<fac[c0]*fac[c1]%mod*pw[cnt]%mod<<'\n';
	}
	return 0;
}