#include<bits/stdc++.h>
using namespace std;
int n;
int a[1005];
int quan[1000005][105];
int cnt;
int maxx;
int vis[1005];
int vis1[1005];
int lin[1005];
void dfs(int dep){
//	for(int i=1;i<=dep;++i){
//		cout<<lin[i]<<' ';
//	}cout<<'\n';
	if(dep==n*2+1){
		cnt++;
		for(int i=1;i<=n*2;++i){
			quan[cnt][i]=lin[i];
		}
		return ;
	}
	if (a[dep]==0){
		for(int i=1;i<=n*2;++i) {
			if(vis1[i]==0 && vis[i]==0){
				vis[i]=1;
				lin[dep]=i;
				dfs(dep+1);
				vis[i]=0;
			}
		}
	}
	else{
		lin[dep]=a[dep]; 
		dfs(dep+1);
	}
}
int main(){
	cin>>n;
	for(int i=1;i<=n*2;++i){
		cin>>a[i];
		if(a[i]!=0) vis1[a[i]]=1;
	}
	dfs(1);
	for(int i=1;i<=cnt;++i){
		int cnt=0;
		for(int j=1;j<=n*2;j+=2){
			cnt+=abs(quan[i][j]-quan[i][j+1]);
		}
		maxx=max(maxx,cnt);
	}
	cout<<maxx<<'\n';
	int ans=0;
	for(int i=1;i<=cnt;++i){
		int cnt=0;
		for(int j=1;j<=n*2;j+=2){
			cnt+=abs(quan[i][j]-quan[i][j+1]);
		}
		if(cnt==maxx){
			ans++;
			for(int j=1;j<=n*2;++j){
				cout<<quan[i][j]<<' ';
			}cout<<'\n';
		}
	}
	cout<<ans<<'\n';
	return 0;
}

