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
int pos[N];
string s;
vector<int> d[N];

struct Trie {
	int num, idx;
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
	}
	void Build_AC() {
		queue<int> q;
		for (int i = 0; i < 26; i++) if (node[0].ch[i]) q.push(node[0].ch[i]);
		while (!q.empty()) {
			int u = q.front(); q.pop();
			for (int i = 0; i < 26; i++) {
				if (node[u].ch[i]) node[node[u].ch[i]].fail = node[node[u].fail].ch[i];
				else node[u].ch[i] = node[node[u].fail].ch[i];
			}
		}
	}
	void Link() {
		for (int i = 1; i <= num; i++) {
			d[i].emplace_back(node[i].fail);
			d[node[i].fail].emplace_back(i);
		}
	}
}; Trie trie;

vector<pair<int, int> > e[N];

signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> s >> m;
	Trie.Build(s);
	for (int i = 1; i <= m; i++) {
		int v, u;
		cin >> v >> u;
		e[u].emplace_back(make_pair(v, i));
	}
	trie.Build_AC(); trie.Link();
	return 0;
}