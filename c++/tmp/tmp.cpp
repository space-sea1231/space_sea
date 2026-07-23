#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;
typedef long long ll;

const int N = 2e5 + 10;

int n, m, k;
struct Node {
    int a;
    ll b, c;    
    ll ans;
} sub[N];

vector<int> q[N];
int ptr[N];
bool fail[N];

struct EE {
    ll edt;
    int id;
    bool operator>(const EE& other) const {
        return edt > other.edt;
    }
};

void solve() {
    cin >> n >> m >> k;
    k = min(k, n);
    for (int i = 1; i <= m; i++) {
        cin >> sub[i].a >> sub[i].b >> sub[i].c;
    }
    for (int i = 1; i <= n; i++) {
        q[i].clear();
        ptr[i] = 0;
        fail[i] = false;
    }
    set<int> st;
    priority_queue<EE, vector<EE>, greater<EE>> pqend;
    int free = k;
    int sptr = 1;
    ll cur_time = 0;
    while (sptr <= m || !pqend.empty() || !st.empty()) {
        while (free > 0 && !st.empty()) {
            int sub_id = *st.begin();
            st.erase(st.begin());
            int id = sub[sub_id].a;
            sub[sub_id].ans = cur_time; 
            pqend.push({cur_time + sub[sub_id].c, id});
            free--; fail[id] = true; ptr[id]++;
        }
        ll nt = -1;
        if (sptr <= m) nt = sub[sptr].b;
        if (!pqend.empty()) {
            if (nt == -1) nt = pqend.top().edt;
            else nt = min(nt, pqend.top().edt);
        }
        if (nt == -1) break;
        cur_time = nt;
        int team2 = -1;
        if (sptr <= m && sub[sptr].b == cur_time) {
            team2 = sub[sptr].a;
            q[team2].push_back(sptr);
            sptr++;
        }
        vector<int> team;
        while (!pqend.empty() && pqend.top().edt == cur_time) {
            int id = pqend.top().id;
            pqend.pop();
            free++;
            fail[id] = false;
            team.push_back(id);
        }
        if (team2 != -1) {
            if (!fail[team2] && ptr[team2] < q[team2].size()) {
                st.insert(q[team2][ptr[team2]]);
            }
        }
        for (int id : team) {
            if (ptr[id] < q[id].size()) {
                st.insert(q[id][ptr[id]]);
            }
        }
    }
    for (int i = 1; i <= m; i++) printf("%d ", sub[i].ans);
    printf("\n");
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}