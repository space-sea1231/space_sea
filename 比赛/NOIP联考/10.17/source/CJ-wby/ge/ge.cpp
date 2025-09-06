//09 48 6pts
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
const int N=16+5,mod=998442353,W=2e5+5;
int p[N][N],dis[N][N],tmp[N],jc[W],fas[N][N],t[N];
bool s[N];
int fpow(int a,int b){
	if(b<=0){
		return 1;
	}
	if(b%2==0){
		int tmp=fpow(a,b/2);
		return tmp*tmp%mod;
	}
	return a*fpow(a,b-1)%mod;
} 
void help(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			cin>>p[i][j];
		}
	}
	for(int i=1;i<=m;i++){
		cin>>s[i];
	}
	for(int i=1;i<=m;i++){
		for(int j=1;j<=m;j++){
			int cnt=0;
			for(int k=1;k<=n;k++){
				dis[i][j]+=abs(p[i][k]-p[j][k]);
				if(p[i][k]!=p[j][k]){
					t[++cnt]=abs(p[i][k]-p[j][k]);
				}
			}
			sort(t+1,t+1+cnt);
			fas[i][j]=1;
			for(int k=1;k<=cnt;k++){
				if(t[k]==0){
					continue;
				}
				fas[i][j]*=t[k];
				fas[i][j]%=mod; 
			}
			fas[i][j]=fpow(fas[i][j],cnt-1);
			if(n==1){
				fas[i][j]=1;
			}
			if(i==j){
				fas[i][j]=1;
			}
//			cerr<<i<<" "<<j<<":"<<fas[i][j]<<endl;
		}
		tmp[i]=i;
	}
//	cerr<<endl;
	int mini=1e18,cnt=0;
	do{
//		cerr<<"?\n";
		if(!s[tmp[1]]){
			continue;
		}
		int ans=0,fa=1;
		for(int i=2;i<=m;i++){
			ans+=dis[tmp[i-1]][tmp[i]];
			fa*=fas[tmp[i-1]][tmp[i]];
			fa%=mod;
//			cerr<<"From "<<tmp[i-1]<<" to "<<tmp[i]<<", fas="<<
//			fas[tmp[i-1]][tmp[i]]<<endl;
		}
		if(ans<mini){
			mini=ans;
			cnt=0;
//			cerr<<"Clear!\n";
		}
		if(ans==mini){
//			cerr<<fa<<endl;
			cnt+=fa;
			cnt%=mod;
		}
	}while(next_permutation(tmp+1,tmp+1+m));
	if(mini==1e18){
		cout<<"NIE";
		return;
	}
	cout<<mini<<" "<<cnt;
	return;
}
signed main(){
	freopen("ge.in","r",stdin);
	freopen("ge.out","w",stdout);
	jc[0]=1;
	for(int i=1;i<=2e5;i++){
		jc[i]=jc[i-1]*i;
		jc[i]%=mod;
//		cerr<<i<<" "<<jc[i]<<endl;
	}
	int t;
	cin>>t;
	while(t--){
		help();
		cout<<endl;
	}
	return 0;
}
/*
2
2 2
-1 1
1 -1
1 1
1 3
-41719
100
41719
0 1 0
*/

