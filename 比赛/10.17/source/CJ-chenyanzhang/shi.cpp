#include<bits/stdc++.h>
using namespace std;
int t,ans,n;
string p;
int main(){
	freopen("shi.in","r",stdin);
	freopen("shi.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--){
		cin>>p;
		n=p.size();
		p=" "+p;
		if(n==3){
			if(p[2]=='0'){
				if(p[1]==p[3]) ans=2;
				else ans=1;
			}else{
				ans=1;
				if(p[1]=='1') ans++;
				if(p[3]=='1') ans++;
			}
		}else ans=n-1;
		cout<<ans<<' '<<0<<"\n\n";
	}
	return 0;
}
