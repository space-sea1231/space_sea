#include<bits/stdc++.h>
using namespace std;
int n;
string s;
void run()
{
    cin>>s;
    n=s.size();
    s=' '+s;
    int cnt=0;
    for(int i=1;i<=n;i++) cnt+=s[i]=='0';
    if(!cnt) cout<<n<<'\n';
    else cout<<n-1<<'\n';
} 
signed main()
{
    freopen("1.in","r",stdin);
    freopen("2.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
    int t;
    cin>>t;
    while(t--) run();
	return 0;
}
