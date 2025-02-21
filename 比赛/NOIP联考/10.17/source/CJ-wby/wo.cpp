//07 45 10pts
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
const int N=2e6+5,mod=998244353;
int p[N],tmp[N],a[N];
bool vis[N];
int help(){
	int n;
	cin>>n;
	n*=2;
	for(int i=1;i<=n;i++){
		vis[i]=false;
	}
	for(int i=1;i<=n;i++){
		cin>>p[i]; 
		vis[p[i]]=true;
	}
	int m=0;
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			tmp[++m]=i;
		}
	}
	int maxi=-1e9,cnt=0;
	do{
		int pos=0;
		for(int i=1;i<=n;i++){
			if(p[i]!=0){
				a[i]=p[i];
			}
			else{
				a[i]=tmp[++pos];
			}
		}
		int sum=0;
		for(int i=1;i<=n;i+=2){
			sum+=abs(a[i]-a[i+1]);
		}
		if(sum>maxi){
			maxi=sum;
			cnt=0;
		}
		if(sum==maxi){
			cnt++;
		}
	}while(next_permutation(tmp+1,tmp+1+m));
	return cnt;
}
signed main(){
	freopen("wo.in","r",stdin);
	freopen("wo.out","w",stdout);
	int t;
	cin>>t;
	while(t--){
		cout<<help()<<endl;
	}
	return 0;
}
/*
hack:
1
3
0 0 4 6 0 5 

ans:
2
*/
