#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#define __Debug

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e5 + 10;

int type, n, q, m;
vector<int> p[N];

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> type >> n >> q >> m;
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        p[a].emplace_back(i);
    }
    while (q--) {
        int l, last = 0;
        bool flag = true;
        cin >> l;
        for (int i = 1; i <= l; i++) {
            int a;
            cin >> a;
            if (!flag) continue;
            auto ptr = lower_bound(p[a].begin(), p[a].end(), last + 1);
            if (ptr == p[a].end()) flag = false;
            else last = *ptr;
        }
        if (flag) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}