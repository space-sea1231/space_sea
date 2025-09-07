#include <bits/stdc++.h>

using namespace std;

#define all(x) begin(x), end(x)
#define len(x) int((x).size())

using ll = long long;
using db = long double;

template <typename T>
inline bool ckmin(T &x, const T &y) {
    return y < x && (x = y, true);
}

template <typename T>
inline bool ckmax(T &x, const T &y) {
    return x < y && (x = y, true);
}

constexpr int N = 305;

int n, a[N];

int calc(int i, int j) {
    swap(a[i], a[j]);
    int ans = 0;
    for (int i = 1, j = 1; i <= n; i = ++j) {
        while (j < n && a[j] < a[j + 1])
            ++j;
        ans += (j - i + 1) * (j - i + 2) / 2;
    }
    swap(a[i], a[j]);
    return ans;
}

void proc() {
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    int ans = calc(1, 1);
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j)
            ckmax(ans, calc(i, j));
    }
    cout << ans << "\n";
}

int main() {
    freopen("wei.in", "r", stdin);
    freopen("wei.out", "w", stdout);
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i)
        proc();
}
