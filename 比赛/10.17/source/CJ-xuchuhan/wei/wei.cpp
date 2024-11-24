#include<bits/stdc++.h>
#define int long long
#define lowbit(x) x&(-x)
using namespace std;
const int N=305;
int T,n,a[N],b[N],dp[N];
int check(int x,int y){
	for(int i=1;i<=n;i++)b[i]=a[i];
	swap(b[x],b[y]);
	int last=1,cnt=0;
	for(int i=1;i<=n;i++){
		if(b[i]<=b[i-1]){
			int len=i-last;
			cnt+=len*(len+1)/2;
			last=i;
		}
	}
	int len=n-last+1;
	cnt+=len*(len+1)/2;
	return cnt;
}
void work(){
	cin>>n;
	int ans=0;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			ans=max(ans,check(i,j));
	cout<<ans<<"\n";
}
signed main(){
	freopen("wei.in","r",stdin);
	freopen("wei.out","w",stdout);
	cin>>T;
	while(T--)work();
	return 0;
}
