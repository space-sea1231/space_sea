#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll NEG = -(1LL << 62);

struct Line {
    ll k = 0, b = NEG;
    ll at(ll x) const { return k * x + b; }
};

bool redundant(const Line &a, const Line &b, const Line &c) {
    return (__int128)(a.b - b.b) * (c.k - b.k)
        >= (__int128)(b.b - c.b) * (b.k - a.k);
}

void append(vector<Line> &h, Line line) {
    if (!h.empty() && h.back().k == line.k) {
        if (h.back().b >= line.b) return;
        h.pop_back();
    }
    while (h.size() >= 2 && redundant(h[h.size() - 2], h.back(), line))
        h.pop_back();
    h.push_back(line);
}

struct History {
    int size = 1;
    vector<vector<Line>> hull;

    explicit History(int n) {
        while (size < n) size *= 2;
        hull.resize(2 * size);
    }

    void add(int position, Line line) {
        for (int p = position + size; p; p /= 2) append(hull[p], line);
    }

    ll query(int l, int r, int mex) const {
        ll answer = NEG;
        auto take = [&](int p) {
            const auto &h = hull[p];
            if (h.empty()) return;
            int left = 0, right = (int)h.size() - 1;
            while (left < right) {
                int mid = (left + right) / 2;
                if (h[mid].at(-mex) <= h[mid + 1].at(-mex)) left = mid + 1;
                else right = mid;
            }
            answer = max(answer, h[left].at(-mex));
        };
        for (l += size, r += size + 1; l < r; l /= 2, r /= 2) {
            if (l & 1) take(l++);
            if (r & 1) take(--r);
        }
        return answer;
    }
};

struct LastOccurrence {
    int size = 1;
    vector<int> minimum;

    explicit LastOccurrence(int n) {
        while (size < n + 2) size *= 2;
        minimum.resize(2 * size);
    }

    void update(int value, int time) {
        int p = value + size;
        minimum[p] = time;
        while (p /= 2) minimum[p] = min(minimum[p * 2], minimum[p * 2 + 1]);
    }

    pair<int, int> segment(int start) const {
        int p = 1, prefix = INT_MAX;
        while (p < size) {
            if (minimum[p * 2] <= start) p *= 2;
            else {
                prefix = min(prefix, minimum[p * 2]);
                p = p * 2 + 1;
            }
        }
        return {p - size, prefix - 1};
    }
};

struct Epoch {
    int mex, l, r, begin, end;
};

vector<Epoch> preprocess(const vector<int> &a, int k) {
    int n = (int)a.size() - 1;
    LastOccurrence last(n);
    vector<int> left(n + 1, -1), right(n + 1, -1), current(n + 1, -1), changed;
    vector<unsigned char> marked(n + 1);
    vector<Epoch> epochs;
    set<int> active;

    auto mark = [&](int m) {
        if (!marked[m]) {
            marked[m] = 1;
            changed.push_back(m);
        }
    };
    auto remove = [&](int m) {
        left[m] = right[m] = -1;
        active.erase(m);
        mark(m);
    };
    auto add = [&](int m, int l, int r) {
        if (left[m] == -1) {
            left[m] = l;
            right[m] = r;
            active.insert(m);
        } else {
            left[m] = min(left[m], l);
            right[m] = max(right[m], r);
        }
        mark(m);
    };

    for (int i = 1; i <= n; ++i) {
        if (i > k) {
            int m = *active.rbegin();
            if (left[m] == right[m]) remove(m);
            else {
                ++left[m];
                mark(m);
            }
        }
        add(0, i - 1, i - 1);
        last.update(a[i], i);
        if (left[a[i]] != -1) {
            int l = left[a[i]], r = right[a[i]];
            remove(a[i]);
            while (l <= r) {
                auto part = last.segment(l);
                int end = min(r, part.second);
                add(part.first, l, end);
                l = end + 1;
            }
        }

        // Record each fixed decision interval and the time when it expires.
        for (int m : changed) {
            if (current[m] != -1) epochs[current[m]].end = i - 1;
            current[m] = -1;
            if (left[m] != -1) {
                current[m] = (int)epochs.size();
                epochs.push_back({m, left[m], right[m], i, n});
            }
            marked[m] = 0;
        }
        changed.clear();
    }
    return epochs;
}

struct SegmentLiChao {
    int n;
    const vector<ll> &x;
    vector<Line> tree;

    // Time is the domain; x[i] is the possibly repeated prefix sum at time i.
    explicit SegmentLiChao(const vector<ll> &coordinates)
        : n((int)coordinates.size() - 1), x(coordinates), tree(4 * n + 4) {}

    void addLine(int p, int l, int r, Line line) {
        if (tree[p].b == NEG) {
            tree[p] = line;
            return;
        }
        int mid = (l + r) / 2;
        if (line.at(x[mid]) > tree[p].at(x[mid])) swap(line, tree[p]);
        if (l == r) return;
        if (line.at(x[l]) > tree[p].at(x[l])) addLine(p * 2, l, mid, line);
        else if (line.at(x[r]) > tree[p].at(x[r]))
            addLine(p * 2 + 1, mid + 1, r, line);
    }

    void addSegment(int p, int l, int r, int ql, int qr, Line line) {
        if (ql <= l && r <= qr) {
            addLine(p, l, r, line);
            return;
        }
        int mid = (l + r) / 2;
        if (ql <= mid) addSegment(p * 2, l, mid, ql, qr, line);
        if (qr > mid) addSegment(p * 2 + 1, mid + 1, r, ql, qr, line);
    }

    ll query(int p, int l, int r, int i) const {
        ll answer = tree[p].at(x[i]);
        if (l == r) return answer;
        int mid = (l + r) / 2;
        if (i <= mid) return max(answer, query(p * 2, l, mid, i));
        return max(answer, query(p * 2 + 1, mid + 1, r, i));
    }
};

ll solve(const vector<int> &a, int k) {
    int n = (int)a.size() - 1;
    vector<ll> sum(n + 1), dp(n + 1);
    for (int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + a[i];
    vector<Epoch> epochs = preprocess(a, k);
    History history(n);
    SegmentLiChao lichao(sum);
    int next = 0;

    for (int i = 1; i <= n; ++i) {
        history.add(i - 1, {sum[i - 1], dp[i - 1]});
        // All decisions in a newly active epoch satisfy j < i.
        while (next < (int)epochs.size() && epochs[next].begin == i) {
            const auto &e = epochs[next++];
            ll b = history.query(e.l, e.r, e.mex);
            lichao.addSegment(1, 1, n, e.begin, e.end, {e.mex, b});
        }
        dp[i] = lichao.query(1, 1, n, i);
    }
    return dp[n];
}

int main() {
    freopen("seq.in", "r", stdin);
    freopen("seq.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    if (!(cin >> n >> k)) return 0;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    cout << solve(a, k) << '\n';
    return 0;
}
