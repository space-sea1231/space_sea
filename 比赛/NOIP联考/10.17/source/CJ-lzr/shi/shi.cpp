#include<bits/stdc++.h>
#define int long long
using namespace std;
int read(){int p=0,flg=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-') flg=-1;c=getchar();}while(c>='0'&&c<='9'){p=p*10+c-'0';c=getchar();}return p*flg;}
int T,n;string s;
void solve(){
	cin>>s;n=s.size();s=" "+s;
	if(n==1){
		if(s==" 0") cout<<"0 0\n";
		else cout<<"1 0\n";
	}else if(n==2){
		if(s==" 00") cout<<"0 0\n";
		else if(s==" 01") cout<<"1 0\n";
		else if(s==" 10") cout<<"1 0\n";
		else if(s==" 11") cout<<"2 0\n";
	}else if(n==3){
		if(s==" 000") cout<<"2 1\n2\n";
		else if(s==" 001") cout<<"1 0\n";
		else if(s==" 010") cout<<"1 0\n";
		else if(s==" 011") cout<<"2 0\n";
		else if(s==" 100") cout<<"1 0\n";
		else if(s==" 101") cout<<"2 0\n";
		else if(s==" 110") cout<<"2 0\n";
		else cout<<"3 0\n";
	}else if(n==4){
		if(s==" 0000") cout<<"2 1\n2\n";
		else if(s==" 0001") cout<<"3 1\n2\n";
		else if(s==" 0010") cout<<"3 2\n2 3\n";
		else if(s==" 0011") cout<<"2 0\n";
		else if(s==" 0100") cout<<"3 2\n3 2\n";
		else if(s==" 0101") cout<<"2 0\n";
		else if(s==" 0110") cout<<"2 0\n";
		else if(s==" 0111") cout<<"3 0\n";
		else if(s==" 1000") cout<<"3 1\n3\n";
		else if(s==" 1001") cout<<"2 0\n";
		else if(s==" 1010") cout<<"2 0\n";
		else if(s==" 1011") cout<<"3 0\n";
		else if(s==" 1100") cout<<"2 0\n";
		else if(s==" 1101") cout<<"3 0\n";
		else if(s==" 1110") cout<<"3 0\n";
		else cout<<"4 0\n";
	}else{
		int cnt=0;for(int i=1;i<=n;i++) cnt+=s[i]-'0';
		cout<<max(n-1,cnt)<<' '<<0<<'\n';
	}
}
signed main(){
	freopen("shi.in","r",stdin);freopen("shi.out","w",stdout);
	T=read();while(T--) solve();
	return 0;
}