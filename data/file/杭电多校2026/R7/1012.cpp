#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5;
int n,f[N],g[N],siz[N];
vector<int> vc[N];
bool cmpf(int x,int y){
	return f[x]<f[y];
}
bool cmpg(int x,int y){
	return siz[x]<siz[y];
}
struct Node{
	int l1,r1,l2,r2;
	int q1[N],q2[N];
	void clr(){l1=l2=1,r1=r2=0;}
	void ins1(int x){q1[++r1]=x;}
	void ins2(int x){q2[++r2]=x;}
	int mi(){
		if(l1>r1)return q2[l2++];
		if(l2>r2)return q1[l1++];
		if(q1[l1]<=q2[l2])return q1[l1++];
		return q2[l2++];
	}
}Q;
void dfs(int x){
	siz[x]=1;
	for(int y:vc[x])dfs(y),f[x]=max(f[x],f[y]+1),siz[x]+=siz[y],g[x]+=g[y]+siz[y];
	sort(vc[x].begin(),vc[x].end(),cmpf),Q.clr();
	for(int y:vc[x])Q.ins1(f[y]+1);
	int all=(int)vc[x].size();
	while(all>2){
		int mi1=Q.mi(),mi2=Q.mi();
		Q.ins2(mi2+1),f[x]=max(f[x],mi2+1),all--;
	}
	sort(vc[x].begin(),vc[x].end(),cmpg),Q.clr();
	for(int y:vc[x])Q.ins1(siz[y]);
	all=(int)vc[x].size();
	while(all>2){
		int mi1=Q.mi(),mi2=Q.mi();
		Q.ins2(mi1+mi2),g[x]+=mi1+mi2,all--;
	}
}
void solve(){
	cin>>n;
	for(int i=1;i<=n;i++)f[i]=g[i]=siz[i]=0,vc[i].clear();
	for(int i=2;i<=n;i++){
		int x; cin>>x;
		vc[x].push_back(i);
	}
	dfs(1);
	cout<<f[1]<<' '<<g[1]<<'\n';
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int tc;
    cin>>tc;
    while(tc--)solve();
    return 0;
}