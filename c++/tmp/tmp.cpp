#include<bits/stdc++.h>

#define ll long long
#define pii pair<int, int>
#define fi first
#define se second

int read() {
	int val = 0, ch = getchar();
	while(!isdigit(ch)) ch = getchar();
	while(isdigit(ch)){
		val = (val << 3) + (val << 1) + (ch ^ 48);
		ch = getchar();
	}
	return val;
}

void write(int x){
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}

using namespace std;

const int MAXN = 1e3 + 5;

int n, k;
int a[MAXN][MAXN];
pii p[MAXN * MAXN];

bool vis[MAXN];

struct Oper{
	int r1, c1, r2, c2;
};

vector<Oper> ans;

int val(int i, int j){
	return (i - 1) * n + j;
}

//しまかぜ、出撃しまーす！
int main(){
//	freopen("mischief.in", "r", stdin);
//	freopen("mischief.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n >> k;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			cin >> a[i][j];
			p[a[i][j]] = {i, j};
		}
	}
	for(int i = 1; i <= n; i++){
		int cur = 1;
		fill(vis + 1, vis + n + 1, 0);
		for(; !vis[cur]; cur = p[val(i, cur)].se) vis[cur] = 1;
		fill(vis + 1, vis + n + 1, 0);
		for(; !vis[cur]; cur = p[val(i, cur)].se){
//			cout << p[val(i, 2)].se << '\n';
			int v = (i - 1) * n + cur;
			int x = p[v].fi, y = p[v].se;
			if(x != i){
//				cout << cur << '\n';
				ans.push_back({x, y, i, y});
				swap(p[a[i][y]], p[v]);
				swap(a[i][y], a[x][y]);
			}
			vis[cur] = 1;
		}
		fill(vis + 1, vis + n + 1, 0);
		for(int v = (i - 1) * n + cur; !vis[cur]; cur = p[v].se){
			if(p[v] != make_pair(i, cur)){
				int x = p[v].fi, y = p[v].se;
				ans.push_back({x, y, i, cur});
				swap(p[a[i][cur]], p[v]);
				swap(a[i][cur], a[x][y]);
			}
//			cout << cur << '\n';;
			vis[cur] = 1;
		}
		for(int j = 1; j <= n; j++){
			int v = (i - 1) * n + j;
			if(vis[j]) continue;
			int x = p[v].fi, y = p[v].se;
//			cout << v << '\n';
			if(p[v] == make_pair(i, j)) continue;
			if(x == i || y == j){
				ans.push_back({x, y, i, j});
				swap(p[a[i][j]], p[v]);
				swap(a[i][j], a[x][y]);
			}else{
				ans.push_back({x, y, x, j});
				swap(p[a[x][j]], p[v]);
				swap(a[x][j], a[x][y]);
				ans.push_back({x, j, i, j});
				swap(p[a[i][j]], p[v]);
				swap(a[i][j], a[x][j]);
			}
		}
	}
	cout << (int)ans.size() << '\n';
	for(Oper op : ans){
		cout << op.r1 << ' ' << op.c1 << ' ' << op.r2 << ' ' << op.c2 << '\n';
	}

	return 0;
}