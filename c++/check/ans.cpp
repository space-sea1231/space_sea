#include <bits/stdc++.h>
#define _for(i,a,b) for(ll i=a;i<=b;++i)
#define for_(i,a,b) for(ll i=a;i>=b;--i)
#define ll long long
using namespace std;
const ll N=1e5+10,P=2147483648;
ll n,m,w,k,q[N],h[N],z[N],y[N],ans;
struct tree{ll x,y;}t[N];
inline ll rnt(){
	ll x=0,w=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')w=-1;c=getchar();}
	while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return x*w;
}
namespace SZSZ{
	/*树状数组*/
	ll b[N];
	inline ll lowbit(ll x){return x&-x;}
	inline void UpDate(ll x,ll y){
		while(x<=w){
			b[x]=(b[x]+y)%P;
			x+=lowbit(x);
		}
		return;
	}
	inline ll Query(ll x){
        if(x==0)return 0;
		ll sum=0;
		while(x){
			sum=(sum+b[x])%P;
			x-=lowbit(x);
		}
		return sum;
	}
}
namespace LISAN{
	/*离散化*/
	vector<ll>xx,yy;
	inline bool cmp(tree a,tree b){
		if(a.x==b.x)return a.y<b.y;
		return a.x<b.x;
	}
	inline void Add(ll x,ll y){
		xx.push_back(x);
		yy.push_back(y);
		return;
	}
	inline void LiSan(){
		sort(xx.begin(),xx.end());
		sort(yy.begin(),yy.end());
		xx.erase(unique(xx.begin(),xx.end()),xx.end());
		yy.erase(unique(yy.begin(),yy.end()),yy.end());
		_for(i,1,w){
			t[i].x=lower_bound(xx.begin(),xx.end(),t[i].x)-xx.begin()+1;
			t[i].y=lower_bound(yy.begin(),yy.end(),t[i].y)-yy.begin()+1;
			++h[t[i].x],++y[t[i].y];
		}
		sort(t+1,t+w+1,cmp);
		return;
	}
}
namespace SOLVE{
	ll c[N*20][20]={0};
	/*预处理组合数*/
	inline void PreC(){
		c[0][0]=1;
		_for(i,1,w){
			c[i][0]=1;
			_for(j,1,min(k,i))
				c[i][j]=(c[i-1][j]+c[i-1][j-1])%P;
		}
	}
	/*求解*/
	inline ll Solve(){
		PreC();
		_for(i,1,w-1){
			++q[t[i].x];
			++z[t[i].y];
			if(t[i].x==t[i+1].x&&q[t[i].x]>=k&&h[t[i].x]-q[t[i].x]>=k){
				ll up=c[q[t[i].x]][k];
				ll dn=c[h[t[i].x]-q[t[i].x]][k];
				ll ri=SZSZ::Query(t[i+1].y-1)-SZSZ::Query(t[i].y);
				ans+=((up*dn+P)%P*ri+P)%P;
                ans%=P;
			}
			ll u=((c[z[t[i].y]][k]*c[y[t[i].y]-z[t[i].y]][k]+P)%P-(SZSZ::Query(t[i].y)-SZSZ::Query(t[i].y-1)+P)%P+P)%P;
			SZSZ::UpDate(t[i].y,u);
		}
		return ans;
	}
}
int main(){
	n=rnt(),m=rnt(),w=rnt();
	_for(i,1,w){
		t[i].x=rnt(),t[i].y=rnt();
		LISAN::Add(t[i].x,t[i].y);
	}
	k=rnt();
	LISAN::LiSan();
	printf("%lld\n",SOLVE::Solve());
	return 0;
}
/*

*/
