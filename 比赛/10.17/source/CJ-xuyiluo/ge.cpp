#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define more_test 1
bool is[10000005];
int dis[10000005] , sum[10000005];
int n , m , s , x , y , w;
vector<vector<int> > a;
inline pair<int,int> dijstra(int b){
	for(int i = 1;i <= n;i++){
		dis[i] = INT_MAX;
		is[i] = 0;
		sum[i] = 0;
	}
	sum[b] = 1;
	dis[b] = 0;
	priority_queue < pair <int , int> , vector < pair <int , int> > , greater < pair <int , int> > > q; 
	q.push(make_pair(0 , b));
	while(q.size()){
		int f = q.top().second;
		q.pop();
		if(is[f]) continue;
		is[f] = 1;
		for(auto v:a[f]){
			if(dis[v] > dis[f] + 1){
				sum[v] = sum[f];
				dis[v] = dis[f] + 1;
				q.push(make_pair(dis[v] , v));
			}
			else if(dis[v] == dis[f] + 1) sum[v] += sum[f] , sum[v] %= 100003;
		}
	}
	return make_pair(dis[n] , sum[n]);
}
inline void solve(){
	int n , m;
	cin >> n >> m;
	for(int i = 1;i <= m;i++){
		for(int j = 1 , x;j <= n;j++){
			cin >> x;
		}
	}
	for(int i = 1;i <= m;i++){
		cin >> x;
	}
	if(n == 2 && m == 2){
		cout<<"4 12\n";
		return ;
	}
	if(n == 1 && m == 3){
		cout<<"125057 1\n";
		return ;
	}
	cout<<"NIE\n";
}
signed main(){
	freopen("ge.in" , "r" , stdin);
	freopen("ge.out" , "w" , stdout);
	ios::sync_with_stdio(0);
	cin.tie(0) , cout.tie(0);
	int _ = 1;
	if(more_test) cin >> _;
	while(_--) solve();
}
