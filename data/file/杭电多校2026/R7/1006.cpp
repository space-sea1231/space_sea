#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
int n, m;
pair<int, int> p[200005];
vector<int> vl[200005], vr[200005];
multiset<int> st;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int tc;
    cin >> tc;
    while (tc--) {
        st.clear();
        int lm = 0;
        cin >> n >> m;
        for (int i = 1; i <= n; i++) vl[i].clear(), vr[i].clear();
        for (int i = 1; i <= m; i++) {
            cin >> p[i].first >> p[i].second;
            if (p[i].first > p[i].second) swap(p[i].first, p[i].second);
            vr[--p[i].second].emplace_back(i);
            vl[p[i].first].emplace_back(i);
            lm = max(lm, p[i].first);
        }
        int a1 = -1, a2;
        for (int i = 1, cl = 1, cr = n; i < n; i++) {
            for (auto v : vl[i]) st.insert(i);
            for (auto v : vr[i - 1]) {
                cl = max(cl, p[v].first);
                cr = min(cr, p[v].second);
                st.erase(st.find(p[v].first));
            }
            if (cl > cr || i < lm) continue;
            if (!st.size() || cl < *st.begin()) {
                a1 = cl + 1, a2 = i + 1;
                break;
            }
        }
        if (a1 == -1) cout << "No\n";
        else cout << "Yes\n" << a1 << " " << a2 << "\n";
    }
    return 0;
}