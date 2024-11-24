#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=5e4+5,MOD=4294967296;
int T,n,p[N];
signed main(){
	freopen("wei.in","r",stdin);
	freopen("wei.out","w",stdout);
	scanf("%lld",&T);
	while(T--){
		scanf("%lld",&n);
		memset(p,0,sizeof(p));
		int ans=0,cnt=0;
		for (int i=1;i<=n;i++){
			scanf("%lld",&p[i]);
			if (p[i]>p[i-1]){
				cnt++;
			}else{
				ans+=(cnt+1)*cnt/2;cnt=1;
			}			
		}ans+=(cnt+1)*cnt/2;cnt=0;
		for (int i=1;i<=n;i++){
			for (int j=i+1;j<=n;j++){
				swap(p[i],p[j]); 
				if (p[i]<p[i-1]&&p[i]>p[i+1]&&p[j]<p[j-1]&&p[j]>p[j+1]){
					swap(p[i],p[j]);
					continue;
				}
				int sum=0,cnt=0;
				for (int k=1;k<=n;k++){
					if (p[k]>p[k-1]){
						cnt++;
					}else{
						sum+=(cnt+1)*cnt/2;cnt=1;
					}
//					cout<<p[k]<<' ';
				}
				sum+=(cnt+1)*cnt/2; 
//				cout<<endl<<sum<<endl;
				swap(p[i],p[j]);
				ans=max(ans,sum);
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}

