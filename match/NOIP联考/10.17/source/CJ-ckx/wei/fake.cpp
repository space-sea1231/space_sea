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

constexpr int N = 4e5 + 5;

int n, a[N], bg[N], ed[N];
int top, st[N], pre[N], nxt[N];

ll calc() {
    int ans = n;
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            if (a[j] < a[j - 1])
                break;
            ++ans;
        }
    }
    return ans;
}

ll calc(int i, int j) {
    swap(a[i], a[j]);
    ll ans = calc();
    swap(a[i], a[j]);
    return ans;
}

void proc() {
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    for (int i = 1, j = 1; i <= n; i = ++j) {
        while (j < n && a[j] < a[j + 1])
            ++j;
        fill(bg + i, bg + j + 1, i);
        fill(ed + i, ed + j + 1, j);
    }
    st[top = 0] = 0;
    for (int i = 1; i <= n; ++i) {
        while (top && a[i] < a[st[top]])
            --top;
        pre[i] = st[top], st[++top] = i;
    }
    st[top = 0] = n + 1;
    for (int i = n; i; --i) {
        while (top && a[i] > a[st[top]])
            --top;
        nxt[i] = st[top], st[++top] = i;
    }
    ll ans = calc();
    for (int i = 1; i <= n; ++i) {
        if (bg[i - 1] > 1)
            ckmax(ans, calc(i, bg[i - 1] - 1));
        ckmax(ans, calc(i, pre[i - 1] + 1));
    }
    for (int i = 1; i < n; ++i) {
        ckmax(ans, calc(i, i + 1));
        if (ed[i + 1] < n)
            ckmax(ans, calc(i, ed[i + 1] + 1));
        if (nxt[i] <= n)
            ckmax(ans, calc(i, nxt[i]));
    }
    for (int i = 1; i < n; ++i) {
        ckmax(ans, calc(i, i + 1));
        int j = ed[i + 1] + 1;
        if (j <= n && a[j] < a[i + 1] && a[j - 1] < a[i])
            ckmax(ans, calc(i, j));
    }
    cout << unsigned(ans) << "\n";
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
