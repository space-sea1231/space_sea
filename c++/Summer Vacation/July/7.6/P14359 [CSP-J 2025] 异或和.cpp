#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <map>
#define __Debug

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;

int n, m;
map<int, int> q;

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    int sum = 0, ans = 0, last = 0;
    q[0] = 0;
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        sum ^= a;
        if (q.find(sum ^ m) != q.end() && q[sum ^ m] >= last) {
            ans++;
            last = i;
            cerr<<i<<' ' << a << endl;
            // cerr << i << " " << q[sum ^ m] << endl;
        }
        q[sum] = i;
    }
    // cerr<<q[1];
    printf("%d\n", ans);
    return 0;
}
/*
10
01  11
00  11
11  00
*/