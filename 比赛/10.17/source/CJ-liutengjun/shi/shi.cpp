#include<bits/stdc++.h>
using namespace std;
void solve(){
	string s;
	cin>>s;
	if(s.size()==1)cout<<(s[0]-'0')<<" "<<0<<"\n";
	else if(s.size()==2)cout<<(s[0]+s[1]-'0'-'0')<<" "<<0<<"\n";
	else if(s.size()==4)cout<<2<<" "<<0<<"\n";
	else cout<<(s.size()-1)<<" "<<0<<"\n";
}
signed main() {
	freopen("shi.in","r",stdin);
	freopen("shi.out","w",stdout);
	int T;
	cin>>T;
	while(T--)solve();
	return 0;
}

