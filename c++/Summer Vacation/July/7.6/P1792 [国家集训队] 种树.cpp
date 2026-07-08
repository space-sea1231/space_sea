#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <queue>
#define __Debug

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 2e5 + 10;

int n, m;
int ans;
int a[N];
int vis[N];

struct Node {
    int val;
    int l, r;
};
struct Cmp {
    int val, pos;
    
    bool operator<(const Cmp src) const {
        return val < src.val;
    }
};

Node node[N];
priority_queue<Cmp> q;

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    if (m * 2 > n) {
        printf("Error!\n");
        return 0;
    }
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        node[i].l = i - 1;
        node[i].r = i + 1;
        node[i].val = a[i];
        q.push({a[i], i});
    }
    node[1].l = n, node[n].r = 1;
    for (int i = 1; i <= m; i++) {
        while (vis[q.top().pos]) q.pop();
        Cmp cur = q.top(); q.pop();
        ans += cur.val;
        vis[node[cur.pos].l] = vis[node[cur.pos].r] = 1;
        node[cur.pos].val = node[node[cur.pos].l].val + node[node[cur.pos].r].val - node[cur.pos].val;
        node[cur.pos].l = node[node[cur.pos].l].l;
        node[cur.pos].r = node[node[cur.pos].r].r;
        node[node[cur.pos].l].r = cur.pos;
        node[node[cur.pos].r].l = cur.pos;
        q.push({node[cur.pos].val, cur.pos});
    }
    printf("%d\n", ans);

    return 0;
}
/*
迟暮之年
姗姗来迟
愚公移山
自言自语
和而不同
同心协力
里应外合
*/