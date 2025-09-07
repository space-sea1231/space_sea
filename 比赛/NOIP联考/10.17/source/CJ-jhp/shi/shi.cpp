#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e6+5;
string a;
int t,n;
int main(){
	freopen("shi.in","r",stdin);
	freopen("shi.out","w",stdout);
	cin>>t;
	while(t--){
		cin>>a;
		int tot=0;
		for(int i=0;i<a.length();i++){
			if(a[i]=='1'){
				tot++;
			}
		}
		cout<<tot<<" "<<0<<'\n'<<'\n';
	}
}
