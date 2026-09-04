#include<bits/stdc++.h>
using namespace std;

struct node {
	int v, w;  // 目标点，损失血量 
};
const int N = 1e4 + 10;
vector<node> G[N];
int f[N], u[N];  // 经过 i 需要花费 f[i]
int d[N];  // 从 1 到各个点损失的最小血量 
bool inq[N];  // 入队标志 
int n, m, b;  // 顶点数, 边数, 血量

bool check(int top) {  // SPFA
    if (f[1] > top) return 0;
	memset(d, 0x3f, sizeof(d));  // 初始化 d 数组为无穷大 
	memset(inq, 0, sizeof(inq));  // 删除入队标记 
	queue<int> q;
	q.push(1);  // 1 入队 
	inq[1] = true;  // 标记 1 已入队 
	d[1] = 0;  // 1->1 损失血量 0 
	while(!q.empty()) {
		int u = q.front();  // 取出队首 
		q.pop();  // 队首出队 
		inq[u] = false;  // 删除入队标记 
		for(int i = 0; i < G[u].size(); i++) {
			int v = G[u][i].v, w = G[u][i].w;
			// 到 v 的花费 <= top 
			if(f[v] <= top && d[u] + w < d[v]) {
				d[v] = d[u] + w;
				if(!inq[v]) {
					q.push(v);
					inq[v] = true;
				}
			}
		}
	}
	if(d[n] <= b) return true;
	else return false;
}

int binSearch(int l, int r) {
	int ans = -1;
	while(l <= r) {
		int mid = l + (r-l) / 2;
		if(check(u[mid]) == true) {  // 可行, 缩小点权范围  
			r = mid - 1;
			ans = u[mid];
		}else l = mid + 1;  // 不可行, 扩大点权范围 
	}
	return ans;
}
 
int main(){
	
	cin >> n >> m >> b;
	for(int i = 1; i <= n; i++) {  // 输入点权(花费) 
		cin >> f[i];
		u[i] = f[i];
	}
	for(int i = 0; i < m; i++) {
		int x, y, w;  // x <--w--> y
		cin >> x >> y >> w;
		G[x].push_back({y, w}), G[y].push_back({x, w});
	}
	sort(u + 1, u + n + 1);  // 对点权(花费)升序排列 
	int ans = binSearch(1, n);
	if(ans == -1) cout << "AFK";
	else cout << ans; 
	
	return 0;
} 