#include<bits/stdc++.h>
using namespace std;
int t,n;
string s;
bool a[1000006];
unsigned long long pw[1000005]={1};
inline bool nand(bool x,bool y){
	return ((x|y)==0);
}
int ans;
unordered_map<unsigned long long,int>dp;
inline void dfs(register int stp,register int sum,register unsigned long long now){
	if(stp>13*n)return ;
	if(dp[now]&&dp[now]<=stp)return ;
	dp[now]=stp,ans=max(ans,sum);
	for(register int i=2;i<n;i++){
		if(a[i]&&!a[i-1]&&!a[i+1])continue;
		bool x=a[i-1],y=a[i+1];unsigned long long xx=now;
		a[i-1]=nand(x,a[i]),a[i+1]=nand(y,a[i]);
		now-=pw[n-i+1]*(x-a[i-1]),now-=pw[n-i-1]*(y-a[i+1]);
		dfs(stp+1,sum-x-y+a[i-1]+a[i+1],now);
		now=x;
		a[i-1]=x,a[i+1]=y;
	}
}
stack<int>ans2;
inline bool dfs2(register int stp,register int sum,register unsigned long long now){
	if(stp>13*n)return 0;
	if(sum==ans)return 1;
	if(dp[now]&&dp[now]<=stp)return 0;
	dp[now]=stp;
	for(register int i=2;i<n;i++){
		if(a[i]&&!a[i-1]&&!a[i+1])continue;
		bool x=a[i-1],y=a[i+1];unsigned long long xx=now;
		a[i-1]=nand(x,a[i]),a[i+1]=nand(y,a[i]);
		now-=pw[n-i+1]*(x-a[i-1]),now-=pw[n-i-1]*(y-a[i+1]);
		bool ff=dfs2(stp+1,sum-x-y+a[i-1]+a[i+1],now);
		now=x;
		a[i-1]=x,a[i+1]=y;
		if(ff){ans2.push(i);return 1;}
	}
	return 0;
}
int main(){
	freopen("shi.in","r",stdin);
	freopen("shi.out","w",stdout);
	cin>>t;
	while(t--){
		cin>>s;
		n=s.size();int sum=0;
		dp.clear(),ans=0;
		unsigned long long now=0;
		bool flag=1,flag1=1;
		for(int i=0;i<n;i++){
			a[i+1]=s[i]-'0',sum+=a[i+1];
			if(a[i+1])flag=0; 
			else flag1=0;
			pw[i+1]=pw[i]*131,now=now*131+(a[i+1]+1);
		}
		if(flag1){
			cout<<n<<" "<<0<<"\n";continue;
		}
		if(flag&&n>=20){
			cout<<n-1<<" "<<0<<"\n";
			continue;
		}
		dfs(0,sum,now);
		cout<<ans<<" ";
		dp.clear();
		dfs2(0,sum,now);
		cout<<ans2.size()<<"\n";
		while(ans2.size()>1)cout<<ans2.top()<<" ",ans2.pop();
		if(!ans2.empty()){
			cout<<ans2.top()<<"\n",ans2.pop();
		} 
	}
	return 0;
}
/*
2
0010
001*/
