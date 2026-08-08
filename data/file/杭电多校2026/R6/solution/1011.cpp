#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>
using namespace std;

struct OnlineClosure {
    struct Node {
        long long key = 0;
        long long val = 0;
        long long sum = 0;
        long long last = 0;
        long long dmax = 0;
        long long tag_base = 0;
        int left = 0;
        int right = 0;
        int size = 0;
        uint32_t priority = 0;
        bool tagged = false;
    };

    static constexpr long long NEG = -(1LL << 60);

    vector<Node> tr;
    int root = 0;
    uint64_t seed;

    explicit OnlineClosure(int reserve_size = 0, uint64_t seed_ = 1) : seed(seed_) {
        tr.reserve(reserve_size + 1);
        tr.push_back(Node{});
    }

    uint32_t rng() {
        seed += 0x9e3779b97f4a7c15ULL;
        uint64_t z = seed;
        z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9ULL;
        z = (z ^ (z >> 27)) * 0x94d049bb133111ebULL;
        z ^= z >> 31;
        return static_cast<uint32_t>(z);
    }

    int size(int x) const {
        return x == 0 ? 0 : tr[x].size;
    }

    long long sum(int x) const {
        return x == 0 ? 0 : tr[x].sum;
    }

    int new_node(long long key, long long val) {
        Node node;
        node.key = key;
        node.val = val;
        node.sum = val;
        node.last = val;
        node.dmax = val - 1;
        node.size = 1;
        node.priority = rng();
        tr.push_back(node);
        return static_cast<int>(tr.size()) - 1;
    }

    void apply_set(int x, long long base) {
        if (x == 0) return;
        Node &o = tr[x];
        long long n = o.size;
        o.tagged = true;
        o.tag_base = base;
        o.val = base + size(o.left) + 1;
        o.sum = base * n + n * (n + 1) / 2;
        o.last = base + n;
        o.dmax = base;
    }

    void push(int x) {
        if (x == 0 || !tr[x].tagged) return;
        Node &o = tr[x];
        long long base = o.tag_base;
        if (o.left) apply_set(o.left, base);
        o.val = base + size(o.left) + 1;
        if (o.right) apply_set(o.right, base + size(o.left) + 1);
        o.tagged = false;
    }

    void pull(int x) {
        Node &o = tr[x];
        int l = o.left, r = o.right;
        o.size = size(l) + 1 + size(r);
        o.sum = sum(l) + o.val + sum(r);
        o.last = r == 0 ? o.val : tr[r].last;
        long long best = NEG;
        if (l) best = max(best, tr[l].dmax);
        best = max(best, o.val - size(l) - 1LL);
        if (r) best = max(best, tr[r].dmax - size(l) - 1LL);
        o.dmax = best;
    }

    int merge(int a, int b) {
        if (a == 0 || b == 0) return a + b;
        if (tr[a].priority < tr[b].priority) {
            push(a);
            tr[a].right = merge(tr[a].right, b);
            pull(a);
            return a;
        } else {
            push(b);
            tr[b].left = merge(a, tr[b].left);
            pull(b);
            return b;
        }
    }

    void split_key(int x, long long key, int &a, int &b) {
        if (x == 0) {
            a = b = 0;
            return;
        }
        push(x);
        if (tr[x].key < key) {
            split_key(tr[x].right, key, tr[x].right, b);
            a = x;
            pull(a);
        } else {
            split_key(tr[x].left, key, a, tr[x].left);
            b = x;
            pull(b);
        }
    }

    void split_size(int x, int need, int &a, int &b) {
        if (x == 0) {
            a = b = 0;
            return;
        }
        push(x);
        if (size(tr[x].left) >= need) {
            split_size(tr[x].left, need, a, tr[x].left);
            b = x;
            pull(b);
        } else {
            split_size(tr[x].right, need - size(tr[x].left) - 1, tr[x].right, b);
            a = x;
            pull(a);
        }
    }

    int first_ge(int x, long long need) {
        if (x == 0) return 1;
        if (tr[x].dmax < need) return size(x) + 1;
        push(x);
        int l = tr[x].left;
        int left_size = size(l);
        if (l && tr[l].dmax >= need) {
            return first_ge(l, need);
        }
        if (tr[x].val - left_size - 1LL >= need) {
            return left_size + 1;
        }
        int res = first_ge(tr[x].right, need + left_size + 1LL);
        return left_size + 1 + res;
    }

    void insert(long long key, long long h) {
        int left_tree, right_tree;
        split_key(root, key, left_tree, right_tree);

        long long previous = left_tree == 0 ? NEG : tr[left_tree].last;
        long long current = max(h, previous + 1);

        int first_ok = first_ge(right_tree, current);
        int affected, rest;
        split_size(right_tree, first_ok - 1, affected, rest);
        apply_set(affected, current);

        int middle = new_node(key, current);
        root = merge(merge(merge(left_tree, middle), affected), rest);
    }

    long long total_sum() const {
        return root == 0 ? 0 : tr[root].sum;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<long long> a(n), b(n);
        for (int i = 0; i < n; ++i) cin >> a[i];
        for (int i = 0; i < n; ++i) cin >> b[i];

        OnlineClosure upper(n, 1000003);
        OnlineClosure lower(n, 2000003);

        for (int i = 0; i < n; ++i) {
            upper.insert(a[i], max(a[i], b[i]));
            lower.insert(-a[i], -min(a[i], b[i]));

            long long answer = 2 * (upper.total_sum() + lower.total_sum());
            if (i) cout << ' ';
            cout << answer;
        }
        cout << '\n';
    }

    return 0;
}
