#include <bits/stdc++.h>
using namespace std;
const int N=2e2+10;
int a[N];
int n, st, ed;
bool vis[N];
struct node{
	int dep, dis;
};
bool check(int dep){
	return dep>=1&&dep<=n;
}
void serch(){
	queue<node> q;
	q.push({st, 0});
	int dep, dis;
	while (!q.empty()){
		dep=q.front().dep;
		dis=q.front().dis;
		q.pop();
		if (vis[dep]) continue;
		vis[dep]=1;
		if (dep==ed){
			printf("%d\n", dis);
			exit(0) ;
		}
		if (check(dep+a[dep])) q.push({dep+a[dep], dis+1});
		if (check(dep-a[dep])) q.push({dep-a[dep], dis+1});
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> st >> ed;
	for (int i=1; i<=n; i++){
		cin >> a[i];
	}
	serch();
	printf("-1");
	
	return 0;
}