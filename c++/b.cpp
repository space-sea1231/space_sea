#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <set>
#include <vector>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 5e5 + 10;

int n;
int a[N];
int tmp[N];
int ans[N];
bool flag[N];
int anss;
set<int> b, u;
vector<int> pos[N];

void Insert(int x) {
    if (x > 1 && !flag[x - 1]) b.erase(x - 1);
    else b.insert(x - 1);
    if (x < n && !flag[x + 1]) b.erase(x);
    else b.insert(x);
    flag[x] = true;
}
void Change(int l, int r, int w) {
    auto it = u.lower_bound(l);
    while (it != u.end() && *it <= r) {
        ans[*it] = w;
        it++;
        u.erase(*it);
    }
}
void Update(int x, int w) {
    auto it = b.lower_bound(x);
    int l = (*--it) + 1, r = *it;
    anss = max(anss, r - l >> 1);
    int mid = l + r >> 1;
    if (flag[l]) Change(l, mid, w);
    if (flag[r]) Change(mid + 1, r, w);
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        tmp[i] = a[i];
        b.insert(i);
        u.insert(i);
    }
    b.insert(0);
    sort(tmp + 1, tmp + n + 1);
    int len = unique(tmp + 1, tmp + n + 1) - tmp - 1;
    for (int i = 1; i <= n; i++) a[i] = lower_bound(tmp + 1, tmp + len + 1, a[i]) - tmp;
    for (int i = 1; i <= n; i++) printf("%d ", a[i]);
    printf("\n");
    for (int i = 1; i <= n; i++) pos[a[i]].emplace_back(i);
    for (int i = 1; i <= len; i++) {
        for (auto j:pos[i]) Insert(j);
        for (auto j:pos[i]) {
            Update(j, i);
            if (j > 1) Update(j - 1, i);
            if (j < n) Update(j + 1, i);
        }
    }
    printf("%d\n", anss);
    for (int i = 1; i <= n; i++) printf("%d ", tmp[ans[i]]);
    return 0;
}
/*
[1 0 1 0] 0 0
1 [1 0] 0 0 0

*/