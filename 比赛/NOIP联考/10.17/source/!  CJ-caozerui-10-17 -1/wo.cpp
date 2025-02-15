#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int ans=1;
int q,n,a[2000005];
bool vis[2000005];
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
	freopen("wo.in","r",stdin);
	freopen("wo.out","w",stdout);
	q=read();
	while(q--){
		ans=1;
		n=read();
		for(int i=1;i<=2*n;i++) a[i]=read();
		for(int i=1;i<=2*n;i++) vis[i]=false;
		for(int i=1;i<=2*n;i++){
			if(a[i]) vis[a[i]]=true;
		}
		int cnt=0;
		for(int i=1;i<=2*n;i++){
			if(!vis[i]) cnt++;
		}
		int now0=cnt/2,now1=cnt-cnt/2;
		for(int i=1;i<=n;i++){
			if(a[2*i-1]&&a[2*i]) continue;
			if(!a[2*i-1]&&a[2*i]){
				if(a[2*i]<=n){
					ans=ans*now1%mod;
					now1--;
				}else{
					ans=ans*now0%mod;
					now0--;
				}
			}else if(a[2*i-1]&&!a[2*i]){
				if(a[2*i-1]<=n){
					ans=ans*now1%mod;
					now1--;
				}else{
					ans=ans*now0%mod;
					now0--;
				}
			}
			else{
				ans=ans*now0%mod*now1%mod*2%mod;
				now0--; now1--;
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
