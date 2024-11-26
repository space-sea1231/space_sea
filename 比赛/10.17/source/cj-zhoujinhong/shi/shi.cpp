#include<bits/stdc++.h>
using namespace std;
#define int long long
int T,mx,cnt;
string s;
void dfs(int step,string s,int sum){
	++cnt;
	if(cnt>1e6) return ;
	if(step>13*s.size()) return ;
	if(sum>mx) mx=sum;
	for(int i=1;i<s.size()-1;i++){
		int tot=0;
		char tmp1=s[i-1],tmp2=s[i+1];
		if(s[i]=='0' && s[i-1]=='0') s[i-1]='1',++tot;
		else{
			if(s[i-1]=='1') --tot;
			s[i-1]='0';
		}
		if(s[i]=='0' && s[i+1]=='0') s[i+1]='1',++tot;
		else{
			if(s[i+1]=='1') --tot;
			s[i+1]='0';
		}
		dfs(step+1,s,sum+tot);
		s[i-1]=tmp1;
		s[i+1]=tmp2;
	}
	return ;
}
signed main(){
	freopen("shi.in","r",stdin);
	freopen("shi.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--){
		cin>>s;
		mx=0,cnt=0;
		for(int i=0;i<s.size();i++) mx+=(s[i]=='1');
		dfs(1,s,mx);
		cout<<mx<<" "<<0<<'\n';
	}
	return 0;
}

