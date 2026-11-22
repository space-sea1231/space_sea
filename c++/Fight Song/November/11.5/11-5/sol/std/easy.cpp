#include<bits/stdc++.h> 
#define mod 998244353
#define Fu(i,a,b) for(register int i=a;i<=b;i++)
#define Fd(i,a,b) for(register int i=a;i>=b;i--)
#define fre(x) freopen(#x".in","r",stdin),freopen(#x".out","w",stdout)
using namespace std;
inline int read(){
	int s=0,w=1;char ch=getchar();
	while(ch<'0'||ch>'9'){ if(ch == '-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){s=(s<<1)+(s<<3)+ch-'0';ch=getchar();}
	return s*w;
}
int n,Q,a[1000005],ans[1000005];
int fj[1000005][15],pre[10000005];
int bj[10000005],p[1000005],mp[10000005],cnt;
void sai(){
	Fu(i,2,1e7){
		if(!bj[i]) p[++cnt]=i;
		Fu(j,1,cnt){
			if(p[j]*i>1e7) break;
			bj[p[j]*i]=1,mp[p[j]*i]=p[j];
			if(i%p[j]==0) break;
		}
	}
}
int t[1000005<<2];
void change(int o,int l,int r,int x,int y,int z){
	if(l>=x&&r<=y){
		t[o]=1ll*t[o]*z%mod;
		return ;
	}
	int mid=l+r>>1;
	if(x<=mid) change(o*2,l,mid,x,y,z);
	if(mid<y) change(o*2+1,mid+1,r,x,y,z);
}
int ask(int o,int l,int r,int x){
	if(l==r) return t[o];
	int mid=l+r>>1;
	if(x<=mid) return 1ll*t[o]*ask(o*2,l,mid,x)%mod;
	else return 1ll*t[o]*ask(o*2+1,mid+1,r,x)%mod;
}
struct node{
	int l,r,w;
}q[1000005];
bool cmp(node x,node y){
	return x.r<y.r;
}
int main(){
    fre(easy);
	sai();
	n=read();
	Fu(i,1,n){
		a[i]=read();
		while(mp[a[i]]){
			if(mp[a[i]]!=fj[i][fj[i][0]]) fj[i][++fj[i][0]]=mp[a[i]];
			a[i]/=mp[a[i]];
		}
		if(a[i]!=fj[i][fj[i][0]]) fj[i][++fj[i][0]]=a[i];
	}
	Q=read();
	Fu(i,1,Q) q[i].l=read(),q[i].r=read(),q[i].w=i;
	sort(q+1,q+1+Q,cmp);
	Fu(i,1,4*n) t[i]=1;
	int x=1;
	Fu(i,1,n){
		Fu(j,1,fj[i][0]) change(1,1,n,pre[fj[i][j]]+1,i,fj[i][j]),pre[fj[i][j]]=i;
		while(q[x].r==i) ans[q[x].w]=ask(1,1,n,q[x].l),x++;
	}
	Fu(i,1,Q) printf("%d\n",ans[i]);
	return 0;
}

