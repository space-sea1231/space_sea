#include<bits/stdc++.h>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define polyh vector<p3>
typedef __int128 i128;
typedef long long ll;
typedef long double ld;
using namespace std;
const int N=510,M=5010,INF=0x3f3f3f3f;
const ld eps=1e-19,pi=acosl(-1),inf=1e18;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
template<typename T>
int dcmp(T x) { 
    if(is_same<T,ld>::value)
        return x<-eps?-1:(x>eps?1:0);
    else return (x>0)-(x<0);
}
struct p3{
	ll x,y,z;
	int id;
	p3(ll a=0,ll b=0,ll c=0){x=a,y=b,z=c;}
	p3 &operator +=(const p3 &b){x+=b.x,y+=b.y,z+=b.z;return *this;}
	p3 &operator -=(const p3 &b){x-=b.x,y-=b.y,z-=b.z;return *this;}
	p3 &operator *=(const ld &b){x*=b,y*=b,z*=b;return *this;}
	p3 &operator /=(const ld &b){x/=b,y/=b,z/=b;return *this;}
	friend istream &operator >>(istream &is,p3 &a){return is>>a.x>>a.y>>a.z;}
	friend ostream &operator <<(ostream &os,p3 &a){return os<<'('<<a.x<<','<<a.y<<','<<a.z<<')';}
	bool operator ==(const p3 &a)const{return x==a.x&&y==a.y&&z==a.z;}
	bool operator !=(const p3 &a)const{return x!=a.x||y!=a.y||z!=a.z;}
}O(0,0,0);
p3 operator +(p3 a,p3 b){return p3(a.x+b.x,a.y+b.y,a.z+b.z);}
p3 operator -(p3 a,p3 b){return p3(a.x-b.x,a.y-b.y,a.z-b.z);}
p3 operator *(ll b,p3 a){return p3(b*a.x,b*a.y,b*a.z);}
p3 operator /(p3 a,ll b){return p3(a.x/b,a.y/b,a.z/b);}
p3 operator ^(p3 a,p3 b){return p3(a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x);}
ll operator *(p3 a,p3 b){return a.x*b.x+a.y*b.y+a.z*b.z;}
ll mix(p3 a,p3 b,p3 c){return (a^b)*c;}
ld det(ld a,ld b,ld c,ld d){return a*c-b*d;}
ld dot(p3 a,p3 b){return (ld)a.x*b.x+(ld)a.y*b.y+(ld)a.z*b.z;}
ld crs(p3 a,p3 b){return hypot(det(a.y,a.z,b.z,b.y),det(a.z,a.x,b.x,b.z),det(a.x,a.y,b.y,b.x));}
bool collinear(p3 a,p3 b,p3 c){return ((b-a)^(c-b))==O;}
bool coplanar(p3 a,p3 b,p3 c,p3 p){return !mix(b-a,c-b,p-a);} 
bool above(p3 a,p3 b,p3 c,p3 p){return mix(b-a,c-b,p-a)>0;}
ld angle(p3 a,p3 b,p3 c){
    p3 u=a^b,v=b^c;
    ld op=1;
    if(mix(a,b,c)<0)op=-op;
    ld ang=pi-atan2l(op*crs(u,v),dot(u,v));
    if(ang<=0)ang+=2*pi;
    if(ang>2*pi)ang-=2*pi;
    return ang;
}
ld cutangle(p3 a,p3 b,p3 d,int op){
    ld ang=atan2l(op*crs(a^b,d),-op*dot(a^b,d));
    if(ang<=0)ang+=2*pi;
    return ang;
}
i128 mix128(p3 a,p3 b,p3 c){
    i128 x=(i128)a.y*b.z-(i128)a.z*b.y;
    i128 y=(i128)a.z*b.x-(i128)a.x*b.z;
    i128 z=(i128)a.x*b.y-(i128)a.y*b.x;
    return x*c.x+y*c.y+z*c.z;
}
int T,n,m;
polyh p,q;
ld ans;

void solve(){
	cin>>n>>m;
	ans=0;
	p.resize(n),q.resize(n);
	for(int i=0;i<n;i++)cin>>p[i];
	for(int i=0;i<n;i++)ans+=angle(p[i],p[(i+1)%n],p[(i+2)%n]);
	ans-=(n-2)*pi;
	while(m--){
	    p3 d;
	    cin>>d;
	    vector<int> id,sgn;
	    for(int i=0;i<n;i++){
	    	p3 a=p[i],b=p[(i+1)%n];
	    	int l=dcmp(a*d),r=dcmp(b*d);
	        q[i]=a^b,p[i].id=0;
	        if(l*r<0){
	            id.pb(i);
	            sgn.pb(l>0&&r<0?1:-1);
	        }
	    }
	    for(int i=0,j=id.size();i<j;i++){
	    	if(!~sgn[i])continue;
	    	int u=id[i],v=id[(i+1)%j],w=dcmp(mix128(q[u],q[v],d));
	    	w*=sgn[i]*sgn[(i+1)%j];
	    	assert(w);
	    	p[u].id=p[v].id=w;
		}
	    int cnt=0,tot=0;
	    ld sum=0;
	    for(int i=0;i<n;i++){
	        p3 a=p[i],b=p[(i+1)%n],c=p[(i+2)%n];
	        int l=dcmp(a*d),r=dcmp(b*d);
	        if(r>0)sum+=angle(a,b,c),cnt++;
	        if(l*r<0)sum+=cutangle(a,b,d,p[i].id),cnt++,tot++;
	    }
	    sum=cnt?100*(sum-(cnt-2)*pi)/ans:0;
		if(!tot)sum=clamp(sum,(ld)0,(ld)100);
	    cout<<fixed<<setprecision(20)<<sum<<'\n';
	}
}

int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--)solve();
	return 0;
}
