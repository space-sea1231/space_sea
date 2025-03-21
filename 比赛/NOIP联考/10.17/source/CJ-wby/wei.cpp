//10 57 12pts
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
const int N=4e5+5,mod=(1ll<<32);
int p[N];
int help(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>p[i];
	}
	int maxi=-1e9;
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			int tmp=0,len=0;
			swap(p[i],p[j]);
			for(int k=1;k<=n;k++){
				if(p[k]>p[k-1]){
					len++;
				}
				else{
					len=1;
				}
				tmp+=len;
				tmp%=mod;
			}
			swap(p[i],p[j]);
			maxi=max(maxi,tmp);
		}
	}
	return maxi;
}
signed main(){
	freopen("wei.in","r",stdin);
	freopen("wei.out","w",stdout);
	int t;
	cin>>t;
	while(t--){
		cout<<help()<<endl;
	}
	return 0;
}

