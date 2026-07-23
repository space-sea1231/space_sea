#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

struct Constraint {
    int i, j, y, z;
};

struct TwoSat {
    int vars = 0, nodes = 0;
    vector<int> head, nxt, to;
    vector<int> rhead, rnxt, rto;
    vector<int> comp, val;

    int lit(int x, int v) const {
        return (x - 1) * 2 + v;
    }

    int neg(int u) const {
        return u ^ 1;
    }

    void init(int n, int edge_hint) {
        vars = n;
        nodes = 2 * vars;
        head.assign(nodes, -1);
        rhead.assign(nodes, -1);
        to.clear();
        nxt.clear();
        rto.clear();
        rnxt.clear();
        to.reserve(edge_hint);
        nxt.reserve(edge_hint);
        rto.reserve(edge_hint);
        rnxt.reserve(edge_hint);
        comp.assign(nodes, -1);
        val.assign(vars + 1, 0);
    }

    void add_imp_node(int u, int v) {
        nxt.push_back(head[u]);
        to.push_back(v);
        head[u] = (int)to.size() - 1;

        rnxt.push_back(rhead[v]);
        rto.push_back(u);
        rhead[v] = (int)rto.size() - 1;
    }

    void add_or(int x, int vx, int y, int vy) {
        int a = lit(x, vx), b = lit(y, vy);
        add_imp_node(neg(a), b);
        add_imp_node(neg(b), a);
    }

    void add_unit(int x, int vx) {
        int a = lit(x, vx);
        add_imp_node(neg(a), a);
    }

    bool solve() {
        vector<char> vis(nodes, 0);
        vector<int> order;
        vector<pair<int, int>> st;
        order.reserve(nodes);
        st.reserve(nodes);

        for (int s = 0; s < nodes; ++s) {
            if (vis[s]) continue;
            vis[s] = 1;
            st.push_back({s, head[s]});
            while (!st.empty()) {
                int &e = st.back().second;
                if (e == -1) {
                    order.push_back(st.back().first);
                    st.pop_back();
                    continue;
                }
                int v = to[e];
                e = nxt[e];
                if (!vis[v]) {
                    vis[v] = 1;
                    st.push_back({v, head[v]});
                }
            }
        }

        int cid = 0;
        vector<int> stack2;
        stack2.reserve(nodes);
        for (int p = nodes - 1; p >= 0; --p) {
            int s = order[p];
            if (comp[s] != -1) continue;
            comp[s] = cid;
            stack2.push_back(s);
            while (!stack2.empty()) {
                int u = stack2.back();
                stack2.pop_back();
                for (int e = rhead[u]; e != -1; e = rnxt[e]) {
                    int v = rto[e];
                    if (comp[v] == -1) {
                        comp[v] = cid;
                        stack2.push_back(v);
                    }
                }
            }
            ++cid;
        }

        for (int i = 1; i <= vars; ++i) {
            int f = lit(i, 0), t = lit(i, 1);
            if (comp[f] == comp[t]) return false;
            val[i] = comp[t] > comp[f];
        }
        return true;
    }
};

int calc(int x, char op, int y) {
    if (op == '&') return x & y;
    if (op == '|') return x | y;
    return x ^ y;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n, m, k;
        cin >> n >> m >> k;

        vector<Constraint> cons(k);
        vector<int> has01(m + 1, 0), has10(m + 1, 0);
        for (auto &e : cons) {
            cin >> e.i >> e.j >> e.y >> e.z;
            if (e.y == 0 && e.z == 1) has01[e.j] = 1;
            if (e.y == 1 && e.z == 0) has10[e.j] = 1;
        }

        vector<string> cand(m + 1);
        for (int j = 1; j <= m; ++j) {
            if (has01[j] && has10[j]) cand[j] = "^";
            else if (has01[j]) cand[j] = "|^";
            else if (has10[j]) cand[j] = "&^";
            else cand[j] = "&|";
        }

        TwoSat sat;
        sat.init(n + m, 2 * k * 4 + 10);
        auto op_var = [&](int j) { return n + j; };

        for (int j = 1; j <= m; ++j) {
            if ((int)cand[j].size() == 1) sat.add_unit(op_var(j), 0);
        }

        for (auto e : cons) {
            int xv = e.i;
            int ov = op_var(e.j);
            for (int x = 0; x <= 1; ++x) {
                for (int choice = 0; choice < (int)cand[e.j].size(); ++choice) {
                    char op = cand[e.j][choice];
                    if (calc(x, op, e.y) == e.z) continue;
                    sat.add_or(xv, x ^ 1, ov, choice ^ 1);
                }
            }
        }

        if (!sat.solve()) {
            cout << "NO\n";
            continue;
        }

        cout << "YES\n";
        for (int i = 1; i <= n; ++i) cout << sat.val[i];
        cout << '\n';

        for (int j = 1; j <= m; ++j) {
            int choice = sat.val[op_var(j)];
            if (choice >= (int)cand[j].size()) choice = 0;
            cout << cand[j][choice];
        }
        cout << '\n';
    }
    return 0;
}
