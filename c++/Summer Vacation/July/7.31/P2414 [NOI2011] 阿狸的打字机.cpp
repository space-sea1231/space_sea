#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e5 + 10;

int m;
int idx, cnt, num;
int pos[N], ans[N];
string s;
vector<int> fe[N];
vector<pair<int, int> > e[N];

struct BinaryTree {
	int bin[N];

	int Lowbit(int x) {return x & -x;};
	void Add(int x, int y) {for (int i = x; i <= cnt; i += Lowbit(i)) bin[i] += y;}
	int Query(int x) {
		int res = 0;
		for (int i = x; i; i -= Lowbit(i)) res += bin[i];
		return res;
	}
}; BinaryTree bin;
struct Trie {
	int dfn[N], siz[N];
	struct Node {
		int fa, ed;
		int fail;
		int ch[26];
	}; Node node[N];
	
	int Back(int p) {return node[p].fa;}
	void End(int p) {node[p].ed = ++idx; pos[idx] = p;}
	void Build(string &s) {
		int p = 0, len = s.size();
		for (int i = 0; i < len; i++) {
			// printf("%c", s[i]);
			if (s[i] == 'B') p = Back(p);
			else if (s[i] == 'P') End(p);
			else {
				int &son = node[p].ch[s[i] - 'a'];
				if (!son) {
					son = ++num;
					node[son].fa = p;
				}
				p = son;
			} 
		}
		// printf("\n");
	}
	void Build_AC() {
		queue<int> q;
		for (int i = 0; i < 26; i++) if (node[0].ch[i]) q.push(node[0].ch[i]);
		while (!q.empty()) {
			int u = q.front(); q.pop();
			for (int i = 0; i < 26; i++) {
				if (node[u].ch[i]) {
					int cur = node[u].fail;
					while (cur && !node[cur].ch[i]) cur = node[cur].fail;
					node[node[u].ch[i]].fail = node[cur].ch[i];
					q.push(node[u].ch[i]);
				}
			}
		}
	}
	void Link() {for (int i = 1; i <= num; i++) fe[node[i].fail].emplace_back(i);}
	void Dfs_Fail(int u) {
		dfn[u] = ++cnt;
		siz[u] = 1;
		for (auto v:fe[u]) {
			Dfs_Fail(v);
			siz[u] += siz[v];
		}
	}
	void Dfs_Trie(int u) {
		bin.Add(dfn[u], 1);
		if (node[u].ed) {
			int x = node[u].ed;
			for (auto [v, id] : e[x]) {
				int y = pos[v];
				ans[id] = bin.Query(dfn[y] + siz[y] - 1) - bin.Query(dfn[y] - 1);
			}
		}
		for (int i = 0; i < 26; i++) if (node[u].ch[i]) Dfs_Trie(node[u].ch[i]);
		bin.Add(dfn[u], -1);		
	}
}; Trie trie;

signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> s >> m;
	trie.Build(s);
	for (int i = 1; i <= m; i++) {
		int v, u;
		cin >> v >> u;
		e[u].emplace_back(make_pair(v, i));
	}
	trie.Build_AC(); trie.Link();
	trie.Dfs_Fail(0); trie.Dfs_Trie(0);
	// for (int i = 1; i <= 3; i++) {
	// 	printf("node[%d].fail=%d id=%d\n", i, trie.node[i].fail, trie.node[i].ed);
	// }
	for (int i = 1; i <= m; i++) printf("%d\n", ans[i]);
	return 0;
}
/*
续昨日：今天没梦到黑了，有点遗憾，我还想帮它找回记忆呢
但是你先别急，今天的梦更奇葩
梦境开始了
我出现在了一个游乐园中，能看到的有飞天大转轮和海盗船
但是有些违和感的是，虽然两个游乐设施前都排起了长龙，但是上面却只有一个小孩子在玩
我梦中神奇的脑回路直接默认了那两个小孩是先上去的，他们上去后一下子就来了几百号人
但是我并没有去游玩这几个，而是将目光投向了...过山车
天知道我是怎么想去玩那一看上去就不正常的过山车的，反正在爬上一做不高的假山（过山车出发点在山体内）（但是过山车的起点不应该是在地面吗？）
上去后我的目光直接投向了出口，但是我的潜意识可以意识到：这个过山车不是回路
什么意思呢？你过山车的终点和起点不是一站，那你该如何将一辆重达几吨的过山车弄回起点呢ovo
随后我就坐上了过山车，然后列车开动了
离开山体后看到的是一段笔直的铁轨，而且它是水平的。
嗯，别问我为什么过山车的加速阶段是水平的，因为tm这辆过山车不是靠重力势能加速的，而是牛三！
通俗点讲，这个**过山车上安了个火箭喷射器！
一瞬间，过山车直接就以10m/s^2的速度窜了出去（就是你自由落体的速度）随后开始了一段曲折扭曲让我一生难忘的旅程
90度的弯，以每小时150公里的速度直接转过去了，相当于一头 4 吨多重的成年大象在你身上蹦迪
还有几段爬山下山，如果只是这样还好，问题是这个**过山车它的安全夹是架在你脚上的！（就是平时那个从上面降下来固定在你腰上的）
于是不出意外的，我整个人直接在下山的过程中飞了出去，双手死死的抓住座椅，下半身在空中放飞自我（别问我为什么我下半身又自由了）
终于在下了最后一座小山后。我跌回了座位，然后就是又一个九十度转弯，前方出现了一个架在小塔（大概十几米高吧）上面的...水池。
对，这个**过山车不仅是用火箭喷射器加速的，还是用水池~~减速~~停下来的！
然后在我的潜意识呐喊的注视下，过山车一头撞进了水池，不出所料的没有溅起一滴水，一辆有着150km/h时速的过山车就这么硬生生停下了。就像一个人将手伸进高速旋转的叶片，然后一把抓住叶片将它硬生生停下
然后...我们几个若无其事的走了下来，从一个流着水滑滑梯滑了下去，梦境就这样再次被宿官的起床哨打碎了。
对了，这中间还有个小插曲，我们从滑滑梯上下来时，正好碰上两个从下往上爬的小孩子（对，他们爬的是水滑梯），他们看见我们后就直接调头滑下去了
*/