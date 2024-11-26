#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e6+10;
const int mod=998244353;
int t,n,a[N];
signed main(){
	freopen("wo.in","r",stdin);
	freopen("wo.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n*2;i++) cin>>a[i];
		int mid=n,l=n;
		for(int i=1;i<=n*2-1;i+=2){
			if(a[i]==0||a[i+1]==0) continue;
			l--;
			if(a[i]>a[i+1]) swap(a[i],a[i+1]);
			if(a[i+1]<=mid) mid++;
			else if(a[i]>=mid) mid--;
		} 
		int cnt1=l,cnt2=l,ans=1;
		for(int i=1;i<=n*2-1;i+=2){
			if(a[i]!=0&&a[i+1]!=0) continue;
			if(a[i]!=0){
				if(a[i]<=mid) cnt1--;
				else cnt2--;
			}
			if(a[i+1]!=0){
				if(a[i+1]<=mid) cnt1--;
				else cnt2--;
			}
		}
		cnt1=(cnt1==0)?1:cnt1;
		cnt2=(cnt2==0)?1:cnt2;
		for(int i=1;i<=n*2-1;i+=2){
			if(a[i]!=0&&a[i+1]!=0) continue;
			if(a[i]>a[i+1]) swap(a[i],a[i+1]);
			if(a[i+1]==0){
				ans=ans*2*cnt1%mod*cnt2%mod;
				cnt1-=(cnt1>1)?1:0;
				cnt2-=(cnt2>1)?1:0;
			} 
			if(a[i+1]>mid){ans=ans*cnt2%mod;cnt2-=(cnt2>1)?1:0;}
			if(a[i+1]<=mid){ans=ans*cnt1%mod;cnt1-=(cnt1>1)?1:0;}
		}
		cout<<ans<<"\n";
	}
	return 0;
}
/*
1
1
1 0
*/
