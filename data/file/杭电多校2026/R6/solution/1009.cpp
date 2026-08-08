// author: Mirekintoc Void (QQ: 506007790)

#include <bits/stdc++.h>
using namespace std;

#define N 262150 // (1 << 18) + eps

typedef pair<int, int> pii;
typedef vector<pii> vpii;

int T, n, m, a[N], idx[N];

vpii solve(int l, int r) {
    if (l == r) return { { idx[l], 1 } };
    const int mid = (l + r) >> 1;
    vpii lans = solve(l, mid), rans = solve(mid + 1, r), ans;
    int lsize = lans.size(), rsize = rans.size(), lptr = 0, rptr = 0;
    while (lptr < lsize || rptr < rsize) {
        if (lptr != lsize && (rptr == rsize || lans[lptr].first < rans[rptr].first)) {
            int pos = lans[lptr].first, val = lans[lptr].second;
            lptr++;
            if (!(pos & 1)) {
                if (rptr < rsize && rans[rptr].first == pos + 1) val += rans[rptr++].second;
                if (lptr < lsize && lans[lptr].first == pos + 1) val = max(val, lans[lptr++].second);
            }
            ans.emplace_back(pos >> 1, val);
        }
        else if (lptr == lsize || rans[rptr].first < lans[lptr].first) {
            int pos = rans[rptr].first, val = rans[rptr].second;
            rptr++;
            if (!(pos & 1)) {
                if (lptr < lsize && lans[lptr].first == pos + 1) val += lans[lptr++].second;
                if (rptr < rsize && rans[rptr].first == pos + 1) val = max(val, rans[rptr++].second);
            }
            ans.emplace_back(pos >> 1, val);
        }
        else {
            int pos = lans[lptr].first, x = lans[lptr].second, y = rans[rptr].second;
            lptr++, rptr++;
            if (!(pos & 1)) {
                if (lptr < lsize && lans[lptr].first == pos + 1) y += lans[lptr++].second;
                if (rptr < rsize && rans[rptr].first == pos + 1) x += rans[rptr++].second;
            }
            ans.emplace_back(pos >> 1, max(x, y));
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> T;
    while (T--) {
        cin >> n;
        m = 1 << n;
        for (int i = 0; i < m; i++) {
            cin >> a[i];
            idx[a[i]] = i;
        }
        cout << solve(0, m - 1)[0].second << '\n';
    }
    return 0;
}
