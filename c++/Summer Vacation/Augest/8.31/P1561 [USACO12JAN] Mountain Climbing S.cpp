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

int n;

struct Node {
    int u, d;
};
vector<Node> v1, v2;

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int u, d;
        cin >> u >> d;
        if (u <= d) v1.emplace_back((Node){u, d});
        else v2.emplace_back((Node){u, d});
    }
    sort(v1.begin(), v1.end(), [&](Node s1, Node s2) {
        return s1.u < s2.u;
    });
    sort(v2.begin(), v2.end(), [&](Node s1, Node s2) {
        return s1.d > s2.d;
    });
    int totu = 0, totd = 0;
    queue<int> q;
    for (auto p:v1) {
        totu += p.u;
        while (totd < totu && !q.empty()) {
            totd += q.front();
            q.pop();
        }
        totd = max(totd, totu);
        q.push(p.d);
    }
    while (!q.empty()) {
        totd += q.front();
        q.pop();
    }
    // cerr<<totu << " " << totd << endl;
    // ans = totd, totd -= totu, totu = 0;
    for (auto p:v2) {
        // printf("%d %d\n", p.u, p.d);
        totu += p.u;
        while (totd < totu && !q.empty()) {
            totd += q.front();
            q.pop();
        }
        totd = max(totd, totu);
        q.push(p.d);
        // printf("%d %d\n", totu, totd/);
    }
    while (!q.empty()) {
        totd += q.front();
        q.pop();
    }
    printf("%d\n", totd);
    return 0;
}