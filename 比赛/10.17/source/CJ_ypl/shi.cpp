#include<bits/stdc++.h>
using namespace std;
int t,n;
string s;
vector<int>loc,cz;
int main(){
	freopen("shi.in","r",stdin);
	freopen("shi.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cin>>t;
	while(t--){
		cz.clear();
		loc.clear();
		cin>>s;
		n=s.size();
		s='#'+s;
		for(int i=1;i<=n;i++){
			if(s[i]=='0'){
				loc.push_back(i);
			}
		}
		for(int i=(int)loc.size()-1;i>=1;i--){
			if(i>=2&&loc[i-1]+1==loc[i]){
				for(int j=loc[i-1];j>=loc[i-2]+1;j--){
					cz.push_back(j);
				}
				loc[i-2]=loc[i-2]+1;
				loc.pop_back();
				loc.pop_back();
				i--;
			}
			else if(i!=(int)loc.size()-1&&loc[i-1]+1==loc[i]){
				for(int j=loc[i];j<=loc[i+1]-1;j++){
					cz.push_back(j);
				}
				loc[i-1]=loc[i+1]-1;
				loc.pop_back();
				loc.pop_back();
			}
			else if(i>=1){
				if(((loc[i]-loc[i-1]-1)&1)){
					while(loc[i]-loc[i-1]-1<5&&loc[i]+1<n){
						cz.push_back(loc[i]+2);
						cz.push_back(loc[i]+1);
						cz.push_back(loc[i]+2);
						loc[i]+=2;
					}
					if(loc[i]-loc[i-1]-1<5)continue;
					while(loc[i]-loc[i-1]-1>5){
						cz.push_back(loc[i]-2);
						cz.push_back(loc[i]-1);
						cz.push_back(loc[i]-2);
						loc[i]-=2;
					}
					cz.push_back(loc[i]-1);
					cz.push_back(loc[i-1]+2);
					cz.push_back(loc[i-1]+1);
					cz.push_back(loc[i-1]+2);
					cz.push_back(loc[i]-2);
					cz.push_back(loc[i]-1);
					cz.push_back(loc[i]-2);
					loc[i-1]=loc[i-1]+3;
					loc.pop_back();
				}
				else if((((loc[i]-loc[i-1]-1)&1)==0)&&loc[i]-loc[i-1]-1!=0){
					while(loc[i]-loc[i-1]-1>2){
						cz.push_back(loc[i]-2);
						cz.push_back(loc[i]-1);
						cz.push_back(loc[i]-2);
						loc[i]-=2;
					}
					cz.push_back(loc[i]-2);
					cz.push_back(loc[i]-1);
					cz.push_back(loc[i]-2);
					loc[i-1]=loc[i-1]+1;
					loc.pop_back();
				}
			}
			
		}
		cout<<0<<' '<<cz.size()<<endl;
		for(auto i:cz){
			cout<<i<<' ';
		}
		cout<<endl;
	}
	return 0;
}
