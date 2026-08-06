#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    int n, k, m, q;
    cin >> n >> k >> m >> q;
    unordered_map<string, int> fst, cnt;
    unordered_set<string> ok;
    string last;
    int c = 0;
    vector<int> ans;

    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        if (!fst.count(s)) fst[s] = i;
        ++cnt[s];
        if (s == last)
            ++c;
        else
            last = s, c = 1;
        if (ok.count(s) && i > fst[s] + m && cnt[s] <= q) ans.push_back(i);
        if (c >= k) ok.insert(s);
    }

    if (ans.empty()) {
        cout << "empty\n";
        return;
    }
    for (int i = 0; i < (int)ans.size(); i++) {
        cout << ans[i] << (i + 1 == (int)ans.size() ? "" : " ");
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}
