#include <iostream>
#include <cstring>
using namespace std;

const int N = 1e5 + 10, INF = 1e8;
struct Node {
    int son[2];
    int key, val;
    int cnt, size;
} tr[N];
int n, root, idx;

int get_node(int key) {
    tr[++idx].key = key;
    tr[idx].val = rand();
    tr[idx].cnt = tr[idx].size = 1;
    return idx;
}

void pushup(int p) {
    tr[p].size = tr[tr[p].son[0]].size + tr[tr[p].son[1]].size + tr[p].cnt;
}

// d = 0代表左旋，d = 1代表右旋
void rotate(int& p, int d) {
    int q = tr[p].son[d ^ 1];
    tr[p].son[d ^ 1] = tr[q].son[d], tr[q].son[d] = p, p = q;
	pushup(tr[p].son[d]);
}

void insert(int& p, int key) {
    if (!p) p = get_node(key);
    else if (key < tr[p].key) {
        insert(tr[p].son[0], key);
        if (tr[tr[p].son[0]].val > tr[p].val) rotate(p, 1);
    } else if (key > tr[p].key) {
        insert(tr[p].son[1], key);
        if (tr[tr[p].son[1]].val > tr[p].val) rotate(p, 0);
    } else tr[p].cnt++;

    pushup(p);
}

void remove(int& p, int key) {
    if (!p) return;
    if (key < tr[p].key) remove(tr[p].son[0], key);
    else if (key > tr[p].key) remove(tr[p].son[1], key);
    else if (tr[p].cnt > 1) tr[p].cnt--;
    else if (!tr[p].son[0] && !tr[p].son[1]) p = 0;
    else if (!tr[p].son[1] || (tr[p].son[0] && tr[tr[p].son[0]].val > tr[tr[p].son[1]].val)) {
        rotate(p, 1);
        remove(tr[p].son[1], key);
    } else {
        rotate(p, 0);
        remove(tr[p].son[0], key);
    }

    pushup(p);
}

int get_rank_by_key(int p, int key) {
    if (!p) return 0;
    if (key < tr[p].key) return get_rank_by_key(tr[p].son[0], key);
    else if (key > tr[p].key) return tr[tr[p].son[0]].size + tr[p].cnt + get_rank_by_key(tr[p].son[1], key);
    else return tr[tr[p].son[0]].size + 1;
}

int get_key_by_rank(int p, int rank) {
    if (!p) return INF;
    else if (rank <= tr[tr[p].son[0]].size) return get_key_by_rank(tr[p].son[0], rank);
    else if (rank > tr[tr[p].son[0]].size + tr[p].cnt) return get_key_by_rank(tr[p].son[1], rank - tr[tr[p].son[0]].size - tr[p].cnt);
    else return tr[p].key;
}

int get_prev(int p, int key) {
    if (!p) return -INF;
    if (key <= tr[p].key) return get_prev(tr[p].son[0], key);
    else return max(tr[p].key, get_prev(tr[p].son[1], key));
}

int get_next(int p, int key) {
    if (!p) return INF;
    if (key >= tr[p].key) return get_next(tr[p].son[1], key);
    else return min(tr[p].key, get_next(tr[p].son[0], key));
}

int main() {
    scanf("%d", &n);
    while (n--) {
        int op, x;
        scanf("%d%d", &op, &x);
        if (op == 1) insert(root, x);
        else if (op == 2) remove(root, x);
        else if (op == 3) printf("%d\n", get_rank_by_key(root, x));
        else if (op == 4) printf("%d\n", get_key_by_rank(root, x));
        else if (op == 5) printf("%d\n", get_prev(root, x));
        else if (op == 6) printf("%d\n", get_next(root, x));
    }

    return 0;
}
