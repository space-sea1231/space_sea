#include<bits/stdc++.h>
#define int long long
#define inf 0x3f3f3f3f
using namespace std;
const int mod=998244353,N=20;
int T,n,m,p[N][N],d[N][N],f[N][N],s[N],a[N];
int res[N][N],ansdis=inf,ansf,flag[N];
map<unsigned long long,bool> vis;
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-'0';
		c=getchar();
	}
	return x*f;
} 
int C(int n,int m){
//	cout<<n<<" "<<m<<'\n';
	if(n==m)return 1;
	if(n==1)return m;
	if(n==0||m==0)return 1;
//	if(n>m)return 0;
//	if(res[n][m])return res[n][m];
//	return res[n][m]=
	return (C(n-1,m-1)%mod+C(n,m-1)%mod)%mod;
}
void init(){
	memset(p,0,sizeof p);
	memset(d,0,sizeof d);
	memset(s,0,sizeof s);
	vis.clear();
	for(int i=1;i<=m;i++){
		for(int j=1;j<=m;j++){
			f[i][j]=1;
		}
	}
}
int tt=1;
void dfs(int now,int dis,int fa,int tt){
	bool tempflag=0;
	for(int i=1;i<=m;i++){
		if(i==now||flag[i])continue;
		flag[i]=tt;
//		cout<<"��"<<tt<<"���ߵ�"<<i<<'\n'; 
		tempflag=1;
		dfs(i,dis+d[now][i],fa*f[now][i]%mod,tt+1);
		flag[i]=0;
	}
	if(tempflag==0){
//		cout<<"���յ���\n";
		if(dis<ansdis){
//			cout<<"����disΪ"<<dis<<'\n';
			ansdis=dis;
			ansf=fa;
//			for(int i=1;i<=m;i++)cout<<flag[i]<<" ";
//			cout<<'\n';
//			ansf=1;
//			for(int i=1;i<m;i++){
//				int l,r;
//				for(int j=1;j<=m;j++){
//					if(flag[j]==i)l=j;
//					if(flag[j]==i+1)r=j;
//				}
//				printf("dis[%d][%d]=%lld\n",l,r,d[l][r]);
//				printf("f[%d][%d]=%lld\n",l,r,f[l][r]);
//				(ansf*=f[l][r])%=mod;
//			}
//			cout<<"fa="<<ansf<<'\n';
		}
		else if(dis==ansdis){
//			for(int i=1;i<=m;i++)cout<<flag[i]<<" ";
//			cout<<'\n';
//			for(int i=1;i<m;i++){
//				int l,r;
//				for(int j=1;j<=m;j++){
//					if(flag[j]==i)l=j;
//					if(flag[j]==i+1)r=j;
//				}
//				printf("dis[%d][%d]=%lld\n",l,r,d[l][r]);
//				printf("f[%d][%d]=%lld\n",l,r,f[l][r]);
////				(ansf*=f[l][r])%=mod;
//			}
//			cout<<"fa="<<ansf<<'\n';
			(ansf+=fa)%=mod;
//			cout<<"fa="<<fa<<'\n';
		}
		return;
	}
}
signed main(){
	freopen("ge.in","r",stdin);
	freopen("ge.out","w",stdout);
	T=read();
	while(T--){
		n=read(),m=read();
		init();
		for(int i=1;i<=m;i++){
			for(int j=1;j<=n;j++){
				p[i][j]=read();
			}
		}
		for(int i=1;i<=m;i++)s[i]=read();
		for(int i=1;i<=m;i++){
			for(int j=1;j<=m;j++){
				if(i==j)continue;
				for(int k=1;k<=n;k++){
					d[i][j]+=abs(p[i][k]-p[j][k]);
//					(f[i][j]*=(abs(p[i][k]-p[j][k])+1))%=mod;
				}
				int sum=d[i][j];
				for(int k=1;k<=n;k++){
					(f[i][j]*=C(abs(p[i][k]-p[j][k]),sum)%mod)%=mod;
					sum-=abs(p[i][k]-p[j][k]);
				}
//				printf("f[%d][%d]=%d\n",i,j,f[i][j]);
			}
		}
		ansdis=inf,ansf=0;
		for(int i=1;i<=m;i++){
			if(s[i]==1){
				flag[i]=1;
				dfs(i,0,1,2);
				flag[i]=0;
			}
		} 
		if(ansdis==inf)cout<<"NIE\n";
		else cout<<ansdis<<" "<<ansf<<'\n';
	}
	return 0;
}
/*
T4
above all��ÿ���㵽������ľ���ͷ���������ֱ��Ԥ����
Ȼ������ͼ�϶����������ߣ����ֻ��256����
Ȼ����Ҫ��һ���߷�ʹ��ͼ�ϵ�ÿ���㶼���ߵ����ұ�Ȩ����С 
��һ��ķֿ���ֱ���������� 

100
7 3
2 2 -1 2 0 2 0
2 -1 0 1 -1 0 0
-2 -1 0 -1 2 -1 0
0 0 1
*/
