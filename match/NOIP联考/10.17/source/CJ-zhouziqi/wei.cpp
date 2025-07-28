#include <cstdio>
#include <set>

constexpr int MAXN = 400000 + 2;

int n, p[MAXN];

long long ans;

std::set<std::pair<int, int>> st;

void update(int x) {
    auto it = -- st.lower_bound({x + 1, 0});
    int L = it -> first, R = it -> second;

    if (L < x) {
        st.insert({L, x - 1});
    }
    if (R > x) {
        st.insert({x + 1, R});
    }
    ans -= (R - x + 1) * (x - L + 1) - 1;
    st.erase(it);

    it = st.lower_bound({x, 0});
    auto it2 = it;
    int l = x, r = x;

    if (x > 1 && p[x - 1] <= p[x]) {
        ans += x - (-- it) -> first;
        l = it -> first;
        st.erase(it);
    }
    if (x < n && p[x] <= p[x + 1]) {
        ans += (r - l + 1ll) * (it2 -> second - x);
        r = it2 -> second;
        st.erase(it2);
    }
    st.insert({l, r});
}

void solve() {
    scanf("%d", &n);

    st.clear();
    st.insert({1, n});
    ans = n * (n + 1ll) >> 1;

    for (int i = 1; i <= n; i ++) {
        p[i] = 0;
    }

    for (int i = 1; i <= n; i ++) {
        scanf("%d", &p[i]);
        update(i);
    }

    long long maxAns = ans;
    for (int i = 1; i < n; i ++) {
        for (int j = i + 1; j <= n; j ++) {
            int t = p[i];
            p[i] = p[j];
            update(i);
            p[j] = t;
            update(j);

            maxAns = std::max(maxAns, ans);
            t = p[i];
            p[i] = p[j];
            update(i);
            p[j] = t;
            update(j);
        }
    }

    printf("%lld\n", maxAns);
}

int main() {
    freopen("wei.in", "r", stdin);
    freopen("wei.out", "w", stdout);

    int T;
    scanf("%d", &T);

    while (T --) {
        solve();
    }

    return 0;
}
