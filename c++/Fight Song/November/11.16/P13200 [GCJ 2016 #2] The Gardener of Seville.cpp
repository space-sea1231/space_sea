#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 2e2 + 10;

int T;
int n, m;
char ans[N][N];
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

struct Pair {
	int x, y;
	bool operator<(const Pair &s) const {
		return min(abs(x - y), (n + m << 1) - abs(x - y)) < min(abs(s.x - s.y), (n + m << 1) - abs(s.x - s.y));
	}
	bool operator!=(const Pair &s) const {
		if (x != s.x) return true;
		if (y != s.y) return true;
		return false;
	}
}; Pair p[N];

struct Node {
	int x, y;
	int ori;
}; Node pos[N];

bool Go(int from, int to) {
	int x = pos[from].x, y = pos[from].y;
	int ori = (2 + pos[from].ori) % 4;
	while (1) {
		if (ans[x][y] == ' ') {
			ans[x][y] = ori & 1 ? '/' : '\\';
			// if (from == 7) cerr << ans[x][y] << " ";
		}
		if (ans[x][y] == '\\') {
			if (ori & 1) ori = (ori + 1) % 4;
			else ori = (ori + 3) % 4;
			x += dx[ori];
			y += dy[ori];
		}
		else if (ans[x][y] == '/') {
			ori ^= 1;
			x += dx[ori];
			y += dy[ori];
		}
		if (!(1 <= x && x <= n && 1 <= y && y <= m)) break;
	}
	if (x == pos[to].x + dx[pos[to].ori] && y == pos[to].y + dy[pos[to].ori]) return true;
	return false;
}
int cmp[4] = {0, 1, 2, 3}; 
void Solve(int cur) {
	printf("Case #%d:\n", cur);
	int num = 0;
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			ans[i][j] = ' ';
		}
	}
	for (int i = 1; i <= m; i++) pos[++num] = (Node){1, i, 0};
	for (int i = 1; i <= n; i++) pos[++num] = (Node){i, m, 1};
	for (int i = m; i; i--) pos[++num] = (Node){n, i, 2};
	for (int i = n; i; i--) pos[++num] = (Node){i, 1, 3};
	for (int i = 1; i <= n + m; i++) cin >> p[i].x >> p[i].y;
	sort(p + 1, p + n + m + 1);
	for (int i = 1; i <= n + m; i++) {
		if (min(p[i].x, (n + m << 1) - p[i].x + 1) > min(p[i].y, (n + m << 1) - p[i].y + 1)) swap(p[i].x, p[i].y);
		if (p[i].x < p[i].y) swap(p[i].x, p[i].y);
		if (p[i].x - p[i].y < (n + m << 1) - (p[i].x - p[i].y)) swap(p[i].x, p[i].y);
		// cerr << p[i].x << " " << p[i].y << "\n";
		// cerr << pos[p[i].x].x << " " << pos[p[i].x].y << " " << pos[p[i].y].x << " " << pos[p[i].y].y << "\n";
		if (!Go(p[i].x, p[i].y)) {
			printf("IMPOSSIBLE\n");
			return ;
		}
		// for (int i = 1; i <= n; i++) {
		// 	for (int j = 1; j <= m; j++) {
		// 		printf("%c", ans[i][j]);
		// 	}
		// 	printf("\n");
		// }
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			printf("%c", ans[i][j] == ' ' ? '/' : ans[i][j]);
		}
		printf("\n");
	}
}
signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> T;
	for (int _ = 1; _ <= T; _++) Solve(_);
	return 0;
}
/*
🌌 星空知识卡片 02：参宿四（Betelgeuse）
【📍 基础档案】

坐标：猎户座左肩（α星），距离地球约 548 光年。

视星等：约 0.5 等（不规则变星，在 0.0 到 1.3 等之间波动）。

光谱型：M1-2 型红超巨星（表面温度极低，约 3500 K）。

【📖 文科浪漫与神话】
它的英文名 Betelgeuse 源自阿拉伯语，意为“巨人的手”或“猎户的腋窝”。
在古罗马，人们认为它的闪烁预示着战争。
而在中国古代星官体系中，它属于“参宿”，与心宿二（商星）此起彼落，留下了“人生不相见，动如参与商”（杜甫）的千古名句。

【🔭 硬核数据与物理】

巨大的体量：它的半径大约是太阳的 700 到 900 倍。
如果把参宿四放在太阳的位置，它的表面将吞没火星轨道，甚至逼近木星轨道。

极致的虚胖：尽管体积庞大，但它的质量只有太阳的 16 到 20 倍。
这意味着它的平均密度极低，外层大气极其稀薄。

“大暗化”事件：2020 年初，它的亮度骤降至 1.6 等左右。
后来的研究证实，这是它表面喷出的巨大尘埃云遮挡了视线，而不是它即将爆发的信号。

【💥 未来命运：超新星爆发】
参宿四已经处于恒星演化的末期。
在未来的几万到十几万年内（宇宙时间尺度上的“随时”），它将耗尽核燃料，发生核心坍缩，爆发为超新星。
届时，它的亮度将堪比满月，甚至在白天也能清晰可见，成为人类历史上最壮丽的星空奇观。

【🧭 观测指南】
在冬季夜空中，找到猎户座的“腰带”后，看向左上方那颗微微泛红的亮星，那就是参宿四。
肉眼就能看出它与周围蓝白色恒星的明显颜色差异。
*/