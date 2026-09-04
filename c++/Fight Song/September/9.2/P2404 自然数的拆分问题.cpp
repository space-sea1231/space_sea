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

int n;

vector<int> q;
inline void Print() {
    for (int i = 0, lim = q.size(); i < lim - 1; i++) printf("%d+", q[i]);
    printf("%d\n", q[q.size() - 1]);
}
void Dfs(int cur, int last) {
    if (cur == 0) {
        if (last == n) return;
        Print();
        return;
    }
    for (int i = last; i * 2 <= cur; i++) {
        q.push_back(i);
        Dfs(cur - i, i);
        q.pop_back();
    }
    // if (cur != 1) {
    q.push_back(cur);
    Dfs(0, cur);
    q.pop_back();
    // }
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    Dfs(n, 1);
    return 0;
}