#include<bits/stdc++.h>
#define int long long
#define lowbit(x) x&-x;
#define ls k<<1
#define rs k<<1|1
using namespace std;

const int inf=0x3f3f3f3f3f3f3f3f,mod=1ll<<32;

int T,n,a[400005],ans;

int pre[400005],sp[400005],suf[400005],sf[400005];

int lt[400005],rt[400005];

inline int solve(int A,int B){
	if(A>n||B>n)return 0;
	int res=sp[A-1]+sf[B+1],t1,t2;
	t1=(a[A]>a[A-1]?pre[A-1]+1:1);
	t2=(a[B]<a[B+1]?suf[B+1]+1:1);
	res+=t1+t2; 
	if(A==B-1){
		if(a[A]<a[B])res+=t1*t2;	
	}else{
		int psa=min(rt[A+1],B-1),psb=max(lt[B-1],A+1);
		if(psa==B-1&&psb==A+1){
			res+=(B-A-1)*(B-A-2)/2+(B-A-1);
			if(a[A]<a[A+1]){
				res+=t1*(B-A-1);
			}
			if(a[B-1]<a[B]){
				res+=t2*(B-A-1);
			}
			if(a[A]<a[A+1]&&a[B-1]<a[B]){
				res+=t1*t2;
			}
		}else{
			res+=(psa-A)*(psa-A-1)/2+(psa-A);
			res+=(B-psb)*(B-psb-1)/2+(B-psb);
			res+=sp[psb-1]-sp[psa];
			if(a[A]<a[A+1]){
				res+=t1*(psa-A);
			}
			if(a[B-1]<a[B]){
				res+=t2*(B-psb);
			}
		}
	}
	return res;
}

inline int read(){
	register int x=0,t=0;
	static char ch=getchar();
	while(!isdigit(ch)) t|=(ch=='-'),ch=getchar();
	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return t?-x:x;
}

signed main(){
	freopen("wei.in","r",stdin);
	freopen("wei.out","w",stdout);
	
	T=read();while(T--){
	
	n=read(),ans=0;
	a[0]=a[n+1]=inf;
	for(int i=1;i<=n;i++){
		a[i]=read();
	}
	
	pre[0]=sp[0]=0;
	for(int i=1;i<=n;i++){
		if(a[i]>a[i-1]){
			pre[i]=pre[i-1]+1;
		}else pre[i]=1;
		sp[i]=pre[i]+sp[i-1];
	}
	suf[n+1]=sf[n+1]=0;
	for(int i=n;i>=1;i--){
		if(a[i]<a[i+1]){
			suf[i]=suf[i+1]+1;
		}else suf[i]=1;
		sf[i]=suf[i]+sf[i+1];
	}
	
	for(int i=1,l,r;i<=n;i++){
		l=i,r=n;
		while(l<=r){
			int mid=l+r>>1;
			if(mid-pre[mid]+1<=i)l=mid+1,rt[i]=mid;
			else r=mid-1;
		}
		l=1,r=i;
		while(l<=r){
			int mid=l+r>>1;
			if(mid+suf[mid]-1>=i)r=mid-1,lt[i]=mid;
			else l=mid+1;
		}
	}
	
	for(int i=1;i<=n;i++){
		
//		ans=max(ans,solve(i,i+1);
//		if(i<n)ans=max(ans,solve(i,min(rt[i+1]+1,n)));
//		if(i>1)ans=max(ans,solve(max(lt[i-1]-1,1),i));
		
//		cout<<i<<' '<<rt[i+1]<<" :_____________\n";
		
		for(int j=i+1;j<=n;j++){
			swap(a[i],a[j]);
			ans=max(ans,solve(i,j));
//			cout<<j<<' '<<solve(i,j)<<" kdsb\n";
			swap(a[i],a[j]);
		}
	}
	cout<<ans<<'\n'; 
	
	}return 0;
}
/*
5
3 4 2 1 5 
*/
