#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;

int n, a[N];
vector<int> pos[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    int mx = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pos[a[i]].push_back(i);
        mx = max(mx, a[i]);
    }

    ll ans = 0;

    // mex = 0
    if (pos[0].empty()) {
        cout << 0 << '\n';
        return 0;
    }
    int pre = 0;
    for (int p : pos[0]) {
        int len = p - pre - 1;
        ans += 1LL * len * (len + 1) / 2;
        pre = p;
    }
    int len = n - pre;
    ans += 1LL * len * (len + 1) / 2;

    // mex >= 1
    int L = pos[0].front(), R = pos[0].back();
    for (int m = 1; m <= mx + 1; m++) {
        if (pos[m].empty()) break;

        auto it = lower_bound(pos[m].begin(), pos[m].end(), L);
        if (it != pos[m].end() && *it <= R) {
            // 有 m 在 [L,R] 内，贡献为 0，但仍需更新 L,R
            L = min(L, pos[m].front());
            R = max(R, pos[m].back());
            continue;
        }

        // 所有 m 都在 [L,R] 之外
        int left = 0;
        auto itL = lower_bound(pos[m].begin(), pos[m].end(), L);
        if (itL != pos[m].begin()) {
            --itL;
            left = *itL;
        }

        int right = n + 1;
        auto itR = upper_bound(pos[m].begin(), pos[m].end(), R);
        if (itR != pos[m].end()) {
            right = *itR;
        }

        ans += 1LL * (L - left) * (right - R);

        // 更新覆盖区间
        L = min(L, pos[m].front());
        R = max(R, pos[m].back());
    }

    cout << ans << '\n';
    return 0;
}