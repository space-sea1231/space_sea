#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll N=2e6+10,mod=998244353;
int t,n,p[N],sum1,sum2,sum3,suma,sumb;
ll ans;
vector<int>loc;
int main(){
	freopen("wo.in","r",stdin);
	freopen("wo.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cin>>t;
	while(t--){
		cin>>n;
		loc.clear();
		ans=1;
		sum1=sum2=sum3=suma=sumb=0;
		for(int i=1;i<=2*n;i++){
			cin>>p[i];
			if(p[i]){
				if((i&1)==0&&p[i-1]){
					if(p[i]<=n&&p[i-1]<=n){
						sum1++;
					}
					else if(p[i]>n&&p[i-1]>n){
						sum2++;
					}
					else{
						sum3++;
					}
				}
				loc.push_back(i);
			}
		}
		n=(2*n-sum1*2-sum2*2-sum3*2)/2;
		for(int i=0;i<(int)loc.size();i++){
			if((loc[i]&1)==1&&(i==(int)loc.size()-1||loc[i+1]!=loc[i]+1)){
				if(p[loc[i]]<=sum1*2+sum3+n)suma++;
				else sumb++;
			}
			if((loc[i]&1)==0&&(i==0||loc[i-1]!=loc[i]-1)){
				if(p[loc[i]]<=sum1*2+sum3+n)suma++;
				else sumb++;
			}
		}
		for(int i=0;i<(int)loc.size();i++){
			if(loc[i]&1){
				if(i==(int)loc.size()-1||loc[i+1]!=loc[i]+1){
					if(p[loc[i]]<=sum1*2+sum3+n){
						ans=ans*(n-sumb)%mod;
						sumb++;
					}
					else{
						ans=ans*(n-suma)%mod;
						suma++;
					}
				}
			}
			else{
				if(i==0||loc[i-1]!=loc[i]-1){
					if(p[loc[i]]<=sum1*2+sum3+n){
						ans=ans*(n-sumb)%mod;
						sumb++;
					}
					else{
						ans=ans*(n-suma)%mod;
						suma++;
					}
				}
			}
		}
		while(suma+sumb<2*n){
			ans=ans*(n-suma)%mod*(n-sumb)%mod*2%mod;
			suma++;
			sumb++;
		}
		cout<<ans<<endl;
	}
	return 0;
}
