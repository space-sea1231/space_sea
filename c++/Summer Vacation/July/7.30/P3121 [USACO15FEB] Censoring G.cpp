#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <queue>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e5 + 10;
const int K = 30;

int n;
int idx[N], len[N], pos[N];
int pre[N], nxt[N];
string s, c;

namespace AC {
    int dfn, num;
    struct Node {
        int fail, idx;
		int son[K];
    }; Node node[N];

    void Insert(int idx, string &c) {
		int siz = c.size(), p = 0;
		for (int i = 0; i < siz; i++) {
			if (node[p].son[c[i] - 'a']) p = node[p].son[c[i] - 'a'];
			else p = node[p].son[c[i] - 'a'] = ++dfn;
		}
		node[p].idx = idx;
	}
	void Dfs() {
		queue<int> q;
		for (int i = 0; i < 26; i++) if (node[0].son[i]) q.push(node[0].son[i]);
		while (!q.empty()) {
			int u = q.front(); q.pop();
			for (int i = 0; i < 26; i++) {
				if (node[u].son[i]) {
					node[node[u].son[i]].fail = node[node[u].fail].son[i];
					q.push(node[u].son[i]);
				}
				else node[u].son[i] = node[node[u].fail].son[i];
			}
		}
	}
} using namespace AC;
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> s >> n;
    int siz = s.size(); s = " " + s;
	for (int i = 0; i <= siz; i++) pre[i] = i - 1, nxt[i] = i + 1;
	for (int i = 1; i <= n; i++) {
        cin >> c;
        Insert(idx[i] = i, c);
		len[i] = c.size();
    }
	Dfs();
	// for (int i = 1; i <= siz; i++) pos[i] = node[pos[i - 1]].son[s[i] - 'a'];
	// cerr<<pos[2] << " " << node[1].idx << " " << len[1] << endl;
	for (int i = 1; i <= siz; i = nxt[i]) {
		pos[i] = node[pos[pre[i]]].son[s[i] - 'a'];
		if (node[pos[i]].idx) {
			int cur = i;
			// cerr<<len[node[pos[i]].idx] << " ";
			for (int j = 1; j <= len[node[pos[i]].idx]; j++) cur = pre[cur];
			nxt[cur] = i + 1, pre[i + 1] = cur; i = cur;
			// cerr<<i<<endl;
		}
	}
	for (int i = nxt[0]; i <= siz; i = nxt[i]) printf("%c", s[i]);
    return 0;
}