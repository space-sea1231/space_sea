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
const int N = 2e5 + 10;
const int M = 1e7 + 10;
const int K = 27;

int n, m;
int cnt;
int head[M], to[M], nxt[M];

void Add(int u, int v) {
    to[++cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
}

namespace AC {
    int num;
    int dep[M];
    int ed[M];
    int ch[M][K];
    int fail[M];

    void Insert(string &s) {
        int p = 0, len = s.size();
        for (int i = 0; i < len; i++) {
            if (!ch[p][s[i] - 'a']) ch[p][s[i] - 'a'] = ++num;
            p = ch[p][s[i] - 'a'];
        }
        ed[p]++;
    }
    void Build() {
        queue<int> q;
        for (int i = 0; i < K; i++) {
            if (ch[0][i]) {
                q.push(ch[0][i]);
                Add(0, ch[0][i]);
                // cerr << 0 << " " << ch[0][i] << "\n";
            }
        }
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int i = 0; i < K; i++) {
                if (ch[u][i]) {
                    fail[ch[u][i]] = ch[fail[u]][i];
                    Add(fail[ch[u][i]], ch[u][i]);
                    // cerr << fail[ch[u][i]] << " " << ch[u][i] << "\n";
                    q.push(ch[u][i]);
                } else ch[u][i] = ch[fail[u]][i];
            }
        }
    }
    void Bfs() {
        queue<int> q;
        q.push(0);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int i = head[u]; i; i = nxt[i]) {
                int v = to[i];
                q.push(v);
                dep[v] = dep[u] + ed[v];
            }
        }
    }
    int Dfs(string &a) {
        int p = 0, len = a.size(), rev = 0;
        for (int i = 0; i < len; i++) {
            p = ch[p][a[i] - 'a'];
            rev += dep[p];
        }
        return rev;
    }
} using namespace AC;
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        string a, b;
        cin >> a >> b;
        if (a == b) continue;
        int len = a.size(), l, r;
        for (l = 0; l < len; l++) if (a[l] != b[l]) break;
        for (r = len - 1; ~r; r--) if (a[r] != b[r]) break;
        a.insert(l, "{" + b.substr(l, r - l + 1) + "{");
        Insert(a);
        // printf("%d %d %s\n", l, r, a.c_str());
    }
    Build(); Bfs();
    for (int i = 1; i <= m; i++) {
        string a, b;
        cin >> a >> b;
        if (a.size() != b.size()) { printf("0\n"); continue; }
        int len = a.size(), l, r;
        for (l = 0; l < len; l++) if (a[l] != b[l]) break;
        for (r = len - 1; ~r; r--) if (a[r] != b[r]) break;
        a.insert(l, "{" + b.substr(l, r - l + 1) + "{");
        // printf("%d %d %s\n", l, r, a.c_str());
        printf("%d\n", Dfs(a));
    }
    return 0;
}
/*
Old streets hold wormest stories
老街藏着最暖的故事

天子，黄袍衣，厕所中人，舆论，信任的大臣，漏洞
囚禁，商场底部，

Just when you think you're saved
当你刚刚感到安全时
Just when you've locked your door
当你锁上家门时
It comes like a lightning flash
它如闪电般来临
And the sky is torn
撕裂了整个苍穹
At your back like a loaded gun
背后有已经有上膛的枪
But the fight has just begun
可是战斗才刚刚开场
Steady now breathe, breathe
冷静下来，深呼吸
You can't run
无处可逃
You can't hide
无处可躲
Hold your breath
屏住呼吸
Close your eyes
闭上双眼
Turn your ear to the sky
注意高空
You're not safe here anymore
哪里都不再安全
This is the sound of war
因为这是战争
Just when you think there's a settled score
当你认为尘埃落定
The battle has been reborn
可是战斗再次开始
Comes swift like an avalanche
像一场雪崩
Come to steal what you just got back
毁掉你刚夺回的一切
like a loaded gun
正如指着你背后的那杆上膛的枪
And the night has just begun
夜晚刚刚来临
Steady now breathe, breathe
冷静下来，深呼吸
You can't run
无处可逃
You can't hide
无处可躲
Hold your breath
屏住呼吸
Close your eyes
闭上双眼
Turn your ear to the sky
注意天空
You're not safe here anymore
从此不再安全
This is the sound of war
战争已经敲响！
*/