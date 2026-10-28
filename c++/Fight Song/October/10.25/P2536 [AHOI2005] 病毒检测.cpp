#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#include <bitset>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 5e2 + 10;
const int M = 1e3 + 10;
const int K = 4;

int n;
int len;
string s;
vector<int> q;
bitset<M> vis[N * N];

namespace Trie {
    int num;
    int ch[N * N][K];
    bool v[N * N];

    int Change(char c) {
        if (c == 'A') return 0;
        if (c == 'G') return 1;
        if (c == 'T') return 2;
        if (c == 'C') return 3;
        return -1;
    }
    void Insert(string &s) {
        int p = 0;
        for (int i = 0, lim = s.size(); i < lim; i++) {
            if (!ch[p][Change(s[i])]) ch[p][Change(s[i])] = ++num;
            p = ch[p][Change(s[i])];
        }
        q.emplace_back(p);
    }
    void Dfs(int u, int dep) {
        // if (!u && dep) return ;
        if (dep == len) { v[u] = true; return; }
        if (vis[u][dep]) return ;
        vis[u][dep] = true;
        // cerr<<u<<" " << dep << "\n";
        if (s[dep] != '*' && s[dep] != '?') {
            if(ch[u][Change(s[dep])]) {
                Dfs(ch[u][Change(s[dep])], dep + 1);
            }
        }
        if (s[dep] == '?') {
            for (int i = 0; i < K; i++) {
                if (ch[u][i]) Dfs(ch[u][i], dep + 1);
            }
        }
        if (s[dep] == '*') {
            Dfs(u, dep + 1);
            for (int i = 0; i < K; i++) {
                if (ch[u][i]) {
                    Dfs(ch[u][i], dep);
                    Dfs(ch[u][i], dep + 1);
                }
            }
        }
    }
} using namespace Trie;
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> s >> n;
    len = s.size();
    for (int i = 1; i <= n; i++) {
        string tmp;
        cin >> tmp;
        Insert(tmp);
    }
    Dfs(0, 0);
    int ans = 0;
    for (int p : q) ans += v[p];
    printf("%d\n", n - ans);
    return 0;
}