#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
// #define Debug(x) printf("Debug%d:\n", x);
#define Debug(x) cerr << "Debug" << x << ":\n";
#define int long long 
#define PrintVector(q);\
		for (auto &x:q){\
			printf("%lld ", x);\
		}\
		printf("\n");

using namespace std;
typedef long long ll;

const int N=2e5+10;

struct Ask;
int n, m;
ll ans[N];
vector<int> valx, valy;
vector<Ask> ask;

struct Tree{
	int x, y;
	ll val;
	
	bool operator<(const Tree &a)const{
		return x<a.x;
	}
}tree[N];
struct Ask{
	int x, y;
	int sum, id;
	
	bool operator<(const Ask &a)const{
		return x<a.x;
	}
};
struct BinaryTree{
	ll sum[N];
	inline int Lowbit(int x){
		return x&(-x);
	}
	inline void Add(int x, ll val){
		for (int i=x; i<=n; i+=Lowbit(i)){
			sum[i]+=val;
		}
	}
	inline ll Query(int x){
		ll ans=0;
		for (int i=x; i>=1; i-=Lowbit(i)){
			ans+=sum[i];
		}
		return ans;
	}
}bitree;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	cin >> n >> m;
	for (int i=1; i<=n; i++){
		cin >> tree[i].x >> tree[i].y >> tree[i].val;
		valx.emplace_back(tree[i].x);
		valy.emplace_back(tree[i].y);
	}
	// Debug(1);
	for (int i=1; i<=m; i++){
		int sx, sy, fx, fy;
		cin >> sx >> sy >> fx >> fy;
		ask.emplace_back((Ask){sx-1, sy-1, 1, i});
		ask.emplace_back((Ask){sx-1, fy, -1, i});
		ask.emplace_back((Ask){fx, sy-1, -1, i});
		ask.emplace_back((Ask){fx, fy, 1, i});
		valx.emplace_back(sx-1);
		valy.emplace_back(sy-1);
		valx.emplace_back(fx);
		valy.emplace_back(fy);
	}
	// Debug(2);
	sort(tree+1, tree+n+1);
	sort(ask.begin(), ask.end());
	sort(valx.begin(), valx.end());
	sort(valy.begin(), valy.end());
	valx.erase(unique(valx.begin(), valx.end()), valx.end());
	valy.erase(unique(valy.begin(), valy.end()), valy.end());
	PrintVector(valx);
	PrintVector(valy);
	for (int i=1; i<=n; i++){
		tree[i].x=lower_bound(valx.begin(), valx.end(), tree[i].x)-valx.begin()+1;
		tree[i].y=lower_bound(valy.begin(), valy.end(), tree[i].y)-valy.begin()+1;
		printf("Debug1: %lld %lld\n", tree[i].x, tree[i].y);
	}
	// Debug(3);
	for (auto &cur:ask){
		cur.x=lower_bound(valx.begin(), valx.end(), cur.x)-valx.begin()+1;
		cur.y=lower_bound(valy.begin(), valy.end(), cur.y)-valy.begin()+1;
		printf("Debug2: %lld %lld\n", cur.x, cur.y);
	}
	// Debug(4);
	int cur=1, siz=ask.size();
	for (int i=0; i<siz; i++){
		// Debug(i);
		while (cur<=n&&tree[cur].x<=ask[i].x){
			bitree.Add(tree[cur].y, tree[cur].val);
			cur++;
			// Debug(cur);
		}
		ans[ask[i].id]+=bitree.Query(ask[i].y)*ask[i].sum;
	}
	// Debug(5);
	for (int i=1; i<=m; i++){
		printf("%lld\n", ans[i]);
	}

	return 0;
}