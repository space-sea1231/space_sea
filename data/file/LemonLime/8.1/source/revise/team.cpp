#include <iostream>
#include <stdio.h>
#include <queue>
#define __Debug

using namespace std;
typedef long long ll;

int n;

struct Node {
    int x, y, z;
    int id;
};

Node node[300005];
bool vis[300005];
priority_queue<pair<int, int>> quea, queb, quec;

signed main() {
    freopen("team.in", "r", stdin);
    freopen("team.out", "w", stdout);
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x, y, z;
        cin >> node[i].x >> node[i].y >> node[i].z;
        quea.push(make_pair(node[i].x, i));
        queb.push(make_pair(node[i].y, i));
        quec.push(make_pair(node[i].z, i));
    }
    while (!quea.empty() && !queb.empty() && !quec.empty()) {
        pair<int, int> x = quea.top(), y = queb.top(), z = quec.top();
        int id1 = x.second, id2 = y.second, id3 = z.second;
        if (vis[id1]) quea.pop();
        else if (vis[id2]) queb.pop();
        else if (vis[id3]) quec.pop();
        else if (node[id1].x <= node[id2].x || node[id3].z <= node[id2].z) {
            vis[id2] = 1;
            queb.pop();
        }
        else if (node[id1].x <= node[id3].x || node[id2].y <= node[id3].y) {
            vis[id3] = 1;
            quec.pop();
        }
        else if (node[id2].y <= node[id1].y || node[id3].z <= node[id1].z) {
            vis[id1] = 1;
            quea.pop();
        }
        else {
            printf("%d\n", x.first + y.first + z.first);
            return 0;
        }
    }
    printf("-1\n");
    
    return 0;
}