#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e2 + 10;

int Q;
bool vis[N];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> Q;
    while (Q--) {
        int l1, r1, l2, r2, t;
        cin >> l1 >> r1 >> l2 >> r2 >> t;
        for (int i = l1; i <= r1; i++) vis[i] = false;
        vector<int> q; q.emplace_back(0);
        for (int i = 1; i <= t; i++) {
            int cur = q.front(); q.erase(q.begin());
            q.insert(q.begin() + i / 2, cur); q.emplace_back(i);
        }
        for (int i = l2; i <= r2; i++) vis[q[i]] = true;
        int cnt = 0;
        for (int i = l1; i <= r1; i++) cnt += vis[i];
        printf("%d\n", cnt);
    }
    return 0;
}