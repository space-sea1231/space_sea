#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <deque>
#include <stack>
#define __Debug

using namespace std;
// 1. 定义 int 为 long long 防止数据越界溢出
#define int long long

const int INF = 1e18 + 7;
const int N = 1e5 + 10;

int n, m;
int w[N], h[N];
int f[N];
int sum[N];
int preh[N], prew[N];
stack<int> st;

namespace SegmentTree {
    struct Node {
        int h, vish;
        int minf;
        int minfh;
    };

    Node node[N << 2];

    void Up(int x) {
        node[x].minf = min(node[x << 1].minf, node[x << 1 | 1].minf);
        node[x].minfh = min(node[x << 1].minfh, node[x << 1 | 1].minfh);
    }
    
    // 2. 补全懒标记下传逻辑
    void Down(int x) {
        if (node[x].vish) {
            int ls = x << 1, rs = x << 1 | 1;
            
            node[ls].h = node[ls].vish = node[x].vish;
            node[ls].minfh = node[ls].minf + node[x].vish;
            
            node[rs].h = node[rs].vish = node[x].vish;
            node[rs].minfh = node[rs].minf + node[x].vish;
            
            node[x].vish = 0;
        }
    }
    
    void Build(int x, int l, int r) {
        if (l == r) {
            node[x].h = h[l];
            node[x].minf = node[x].minfh = INF;
            return;
        }
        int mid = (l + r) >> 1;
        Build(x << 1, l, mid);
        Build(x << 1 | 1, mid + 1, r);
        Up(x);
    }
    
    void Change(int x, int l, int r, int L, int R, int y) {
        if (L <= l && r <= R) {
            node[x].h = node[x].vish = y;
            node[x].minfh = node[x].minf + y;
            return ;    
        }
        Down(x); // 调用下传
        int mid = (l + r) >> 1;
        if (L <= mid) Change(x << 1, l, mid, L, R, y); 
        if (mid < R) Change(x << 1 | 1, mid + 1, r, L, R, y); 
        Up(x);
    }
    
    int Query(int x, int l, int r, int L, int R) {
        if (L <= l && r <= R) {
            return node[x].minfh;    
        }
        Down(x); // 调用下传
        int mid = (l + r) >> 1, rev = INF;
        if (L <= mid) rev = min(rev, Query(x << 1, l, mid, L, R)); 
        if (mid < R) rev = min(rev, Query(x << 1 | 1, mid + 1, r, L, R));
        return rev;
    }
    
    void Insert(int x, int l, int r, int p, int y) {
        if (l == r) {
            node[x].minf = y;
            node[x].minfh = node[x].minf + node[x].h;
            return;
        }
        Down(x); // 调用下传
        int mid = (l + r) >> 1;
        if (p <= mid) Insert(x << 1, l, mid, p, y); 
        if (mid < p) Insert(x << 1 | 1, mid + 1, r, p, y); 
        Up(x);
    }
} using namespace SegmentTree;

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> h[i] >> w[i];
    for (int i = 1; i <= n; i++) sum[i] = sum[i - 1] + w[i];
    for (int i = 1; i <= n; i++) {
        while (!st.empty() && h[st.top()] < h[i]) st.pop();
        if (!st.empty()) preh[i] = st.top();
        st.push(i);
    }
    int l = 1;
    for (int r = 1; r <= n; r++) {
        while (sum[r] - sum[l - 1] > m) l++;
        prew[r] = l;
    }
    
    // 删除了原来的 printf 调试语句
    
    Build(1, 1, n);
    // 删除了原先无效的 Insert(1, 1, n, 0, 0);
    
    for (int i = 1; i <= n; i++) {
        // 3. 将插入位置改为在当轮修改之前，且插入的值代表从 i 位置拆分前面部分已产生的最小代价 f[i-1]
        Insert(1, 1, n, i, f[i - 1]);
        
        if (preh[i] + 1 <= i) {
            Change(1, 1, n, preh[i] + 1, i, h[i]);
        }
        f[i] = Query(1, 1, n, prew[i], i);
    }
    
    cout << f[n] << "\n"; // 防止 %d 与 long long 格式不配对，统一用 cout
    return 0;
}