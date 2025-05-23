#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

const int N=5e5+10;

struct Ask;
int n, m;
int tot;
int ans[N];
vector<Ask> ask;

struct Tree{
	int x, y;
	
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
	int sum[N];
	inline int Lowbit(int x){
		return x&(-x);
	}
	inline void Add(int x, int val){
		for (int i=x; i<=n; i+=Lowbit(i)){
			sum[i]+=val;
		}
	}
	inline int Query(int x){
		int ans=0;
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
		cin >> tree[i].x >> tree[i].y;
		tree[i].x++;
		tree[i].y++;
	}
	for (int i=1; i<=m; i++){
		int sx, sy, fx, fy;
		cin >> sx >> sy >> fx >> fy;
		sx++, sy++, fx++, fy++;
		ask.emplace_back((Ask){sx-1, sy-1, 1, i});
		ask.emplace_back((Ask){sx-1, fy, -1, i});
		ask.emplace_back((Ask){fx, sy-1, -1, i});
		ask.emplace_back((Ask){fx, fy, 1, i});
	}
	sort(tree+1, tree+n+1);
	sort(ask.begin(), ask.end());
	int cur=1, siz=ask.size();
	for (int i=1; i<=siz; i++){
		while (cur<=n&&tree[cur].x<=ask[i].x){
			bitree.Add(tree[cur].y, 1);
			cur++;
		}
		ans[ask[i].id]+=bitree.Query(ask[i].x)*ask[i].sum;
	}
	for (int i=1; i<=m; i++){
		printf("%d\n", ans[i]);
	}

	return 0;
}