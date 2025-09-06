#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int t,n;
int p[2000006];
int cnt[2000005];
bool f[2000005];
int ans=0;
inline void dfs(register int x,register int num){
	if(x%2==0&&x){num+=abs(p[x]-p[x-1]);}	
	if(num+((n+n-x+1)/2)*(n+n-2)<ans){
		return ;
	}
	if(x==n*2){
		ans=max(ans,num);
		cnt[num]=(cnt[num]+1)%mod;return ;
	}
	if(p[x+1]){
		dfs(x+1,num);return ;
	}
	for(register int i=1;i<=n*2;i++)
		if(!f[i]){
			f[i]=1;p[x+1]=i;dfs(x+1,num);f[i]=p[x+1]=0;
		}
	return ;
}
signed main(){
	freopen("wo.in","r",stdin);
	freopen("wo.out","w",stdout);
	cin>>t; 
	while(t--){
		cin>>n;
		memset(cnt,0,sizeof(cnt));
		memset(f,0,sizeof(f));
		for(int i=1;i<=2*n;i++){
			cin>>p[i];f[p[i]]=1;
		}
		dfs(0,0); 
		cout<<cnt[ans]<<"\n";
	}
	return 0;
}
/*
6
4
0 0 0 0 0 0 3 0
7
0 0 0 0 0 0 10 0 6 0 0 0 5 0
5
10 0 3 0 6 0 5 0 8 0
2
3 0 2 0
1
1 0
10
0 0 0 0 0 0 0 0 0 0 0 0 12 0 0 0 20 0 0 0
*/
