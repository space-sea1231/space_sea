#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e6+5,MOD=998244353;
int T,n,p[2*N];
signed main(){
	freopen("wo.in","r",stdin);
	freopen("wo.out","w",stdout);
	scanf("%lld",&T);
	while(T--){
		scanf("%lld",&n);
		int cnt1=0,cnt2=0,ans=1;
		int mid=n;memset(p,0,sizeof(p));
		for (int i=1;i<=2*n;i++){
			scanf("%lld",&p[i]);
			if(p[i]&&p[i]<=mid)	cnt1++;
			else if (p[i]&&p[i]>mid)	cnt2++;
		}
		cnt1=n-cnt1;cnt2=n-cnt2;
//		cout<<cnt1<<' '<<cnt2<<endl;
		for (int i=1;i<=n;i++){
//			cout<<cnt1<<' '<<cnt2<<endl; 
			int x=2*i-1,y=2*i;
			if ((p[x]==0&&p[y]!=0)||(p[x]!=0&&p[y]==0)){
				int xx=max(p[x],p[y]);
				if (cnt1==0)	ans=(ans*cnt2--)%MOD;
				else if (cnt2==0)	ans=(ans*cnt1--)%MOD;
				else if (xx<=mid)	ans=(ans*cnt2--)%MOD;
				else	ans=(ans*cnt1--)%MOD;
			}			

		}
//		cout<<cnt1<<' '<<cnt2<<' '<<ans<<endl;
		for (int i=1;i<=n;i++){
			int x=2*i-1,y=2*i;
			if (p[x]==0&&p[y]==0){
				int s=cnt1*cnt2%MOD;
//				if (s==0)	flag=0,
				s=(int)floor((cnt1+cnt2)/2)%MOD*(int)ceil((cnt1+cnt2+1)/2)%MOD;
//				cout<<s<<' '<<cnt2<<' '<<cnt1<<endl;
				ans=(ans*s%MOD)*2%MOD;
				cnt1--,cnt2--;
			}
		}
		printf("%lld\n",max(1ll,ans%MOD));
	}
	return 0;
}
/*
1
4
0 0 0 0 0 0 3 0

1152


1
22
10 39 6 34 0 0 25 24 0 0 29 36 0 0 7 3 18 40 0 0 0 0 0 0 44 5 0 0 0 0 22 21 16 15 2 38 8 23 0 0 12 17 0 0

=
*/
