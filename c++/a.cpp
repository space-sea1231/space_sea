// luogu-judger-enable-o2
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
using namespace std;

inline int geti() {
	int ans = 0; bool flag = 0; char c = getchar();
	while(!isdigit(c)) flag |= c == '-', c = getchar();
	while( isdigit(c)) ans=ans*10+c-'0', c = getchar();
	return flag? -ans: ans;
}

inline void puti(int x) {
	if(x < 0) x=-x, putchar('-');
	if(x > 9) puti(x / 10);
	putchar('0' + x%10);
}

const int maxn = 500 + 10, maxq = 60000 + 5;

struct Numbers {
	int x, y, v; /// (x,y) 位置的值为 v 
	bool operator < (const Numbers& rhs) const {
		return v < rhs.v; /// 用于比较大小 
	}
} Matrix[maxn * maxn]; int mcnt; /// 矩阵中的元素个数

struct BIT {
	int n; /// n * n 的二维树状数组
	int C[maxn][maxn];
	BIT(int N = 0) {n = N; memset(C, 0x00, sizeof(C));} /// 初始化
	inline int lowbit(int x) {return x&(-x);}
	inline void add(int x, int y, int v) { /// 单点修改 
		for(register int i = x; i <= n; i += lowbit(i))
			for(register int j = y; j <= n; j += lowbit(j))
				C[i][j] += v;
	}
	inline int pre(int x, int y) { /// 前缀求和 
		int ans = 0;
		for(register int i = x; i > 0; i -= lowbit(i))
			for(register int j = y; j > 0; j -= lowbit(j))
				ans += C[i][j];
		return ans;
	}
	inline int submat(int x1, int y1, int x2, int y2) { /// 子矩阵和 
		int ans = pre(x2, y2);
		ans -= pre(x1 - 1, y2) + pre(x2, y1 - 1);
		ans += pre(x1 - 1, y1 - 1);
		return ans;
	}
} bit; /// 记得初始化 n

struct Events { /// 记录所有询问 
	int x1, y1, x2, y2, k;
	inline void input() { /// 输入一个询问 
		x1 = geti(); y1 = geti();
		x2 = geti(); y2 = geti();
		k  = geti();
	}
} Querys[maxq];

int bcount(Events mat) { /// 查询某个询问中的黑点个数 
	return bit.submat(mat.x1, mat.y1, mat.x2, mat.y2);
}

int id[maxq], t1[maxq], t2[maxq];
int ans[maxq], cur[maxq];

void Sol(int l, int r, int ql, int qr) {
	if(qr < ql) return; /// 该值域区间没有询问
	if(l == r) {
		for(int i = ql; i <= qr; i ++) ans[id[i]] = Matrix[l].v;
		return; /// 找到解 
	}
	int mid = (l + r)/2;
	for(int i = l; i <= mid; i ++) /// 把要统计到答案中的数值染黑 
		bit.add(Matrix[i].x, Matrix[i].y, 1);
	int cnt1 = 0, cnt2 = 0;
	for(int i = ql; i <= qr; i ++) {
		int u = id[i]; /// 当前要处理的询问
		int s = cur[u] + bcount(Querys[u]); /// 考虑当前区间中的黑点个数
		printf("l=%d r=%d ql=%d qr=%d s=%d\n", l, r, ql, qr, s);
		if(s >= Querys[u].k) t1[++ cnt1] = u;
		else t2[++ cnt2] = u, cur[u] = s; 
	}
	int qcnt = ql - 1;
	for(int i = 1; i <= cnt1; i ++) id[++ qcnt] = t1[i]; /// 左右分组 
	for(int i = 1; i <= cnt2; i ++) id[++ qcnt] = t2[i];
	for(int i = l; i <= mid; i ++) /// 谁污染谁治理 
		bit.add(Matrix[i].x, Matrix[i].y, -1);
	Sol(l, mid, ql, ql + cnt1 - 1);
	Sol(mid+1, r, ql + cnt1, qr);
}

int main() {
	int N = geti(), Q = geti(); bit.n = N;/// 输入矩阵大小和询问组数
	for(int i = 1; i <= N; i ++)
		for(int j = 1; j <= N; j ++)
			Matrix[++ mcnt] = (Numbers){i, j, geti()};
	sort(Matrix + 1, Matrix + mcnt + 1); /// 按元素大小从小到大排序
	for(int i = 1; i <= Q; i ++) Querys[i].input();
	for(int i = 1; i <= Q; i ++) id[i] = i;
	Sol(1, mcnt, 1, Q);
	for(int i = 1; i <= Q; i ++) puti(ans[i]), putchar('\n');
	return 0;
}
