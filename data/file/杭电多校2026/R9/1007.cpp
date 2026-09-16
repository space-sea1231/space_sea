#include<bits/stdc++.h>
using namespace std;
using ull=unsigned long long;

const int P1=1000000007;
const int P2=1000000009;
ull seed1,seed2;
std::mt19937_64 mtrand64(chrono::system_clock::now().time_since_epoch().count());

typedef std::pair<int,int> pii;


struct Node{
	int x=0,y=0;
	Node()=default;
	Node(int _x,int _y):x(_x),y(_y){}
	void add(const Node&o){
		x+=o.x;x%=P1;
		y+=o.y;y%=P2;
	}
	void del(const Node&o){
		x-=o.x-P1;x=x%P1;
		y-=o.y-P2;y=y%P2;
	}
	bool zero()const{return x==0&&y==0;}
};

map<pii,Node>mp;

Node rand(int a,int t,int k){
	if(t==0||t==k)return Node();
	if(mp.count(make_pair(a,t))) return mp[{a,t}];
	return mp[{a,t}] = {mtrand64()%P1,mtrand64()%P2};
}

Node val(int a,int c,int k){
	Node r=rand(a,c+1,k),l=rand(a,c,k);
	r.del(l);
	return r;
}

struct BIT{
	int n;
	vector<Node>tr;
	void init(int _n){n=_n;tr.assign(n+1,Node());}
	void add(int x,Node v){for(;x<=n;x+=x&-x)tr[x].add(v);}
	void build(const vector<int>&a,const vector<int>&c,int k){
		for(int i=1;i<=n;i++){
			add(i,val(a[i],c[i],k));
		}
	}
	Node ask(int x){
		Node r;
		for(;x;x-=x&-x)r.add(tr[x]);
		return r;
	}
	Node query(int l,int r){
		Node x=ask(r),y=ask(l-1);
		x.del(y);
		return x;
	}
};

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	seed1=mtrand64();
	seed2=mtrand64();
	int T;
	if(!(cin>>T))return 0;
	while(T--){
		mp.clear();
		int n,q,k;
		cin>>n>>q>>k;
		vector<int>a(n+1);
		vector<int>c(n+1);
		for(int i=1;i<=n;i++)cin>>a[i];
		for(int i=1;i<=n;i++)cin>>c[i];
		BIT bit;
		bit.init(n);
		bit.build(a,c,k);
		while(q--){
			int op; cin>>op;
			if(op==1){
				int p,nc,x;
				cin>>p>>x>>nc;
				Node now=val(x,nc,k),pre=val(a[p],c[p],k);
				now.del(pre);
				bit.add(p,now);
				a[p]=x;c[p]=nc;
			}else{
				int l,r; cin>>l>>r;
				cout<<(bit.query(l,r).zero()?"YES":"NO")<<'\n';
			}
		}
	}
	return 0;
}
