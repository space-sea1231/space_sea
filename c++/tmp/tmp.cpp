#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

const int MAXN = 5e4 + 10;  // 题目数据上限

// 莫队核心变量
int n, m, k;         // n：序列长度，m：询问数，k：值域
int a[MAXN];         // 存储原数组
int block;           // 分块大小
long long ans[MAXN]; // 存储每个询问的答案（用long long防溢出）
long long now = 0;   // 当前区间的答案
int cnt[MAXN];       // 记录每个数字出现的次数

// 询问结构体：l左端点，r右端点，id原始编号（离线必须记录）
struct Query {
    int l, r, id;
    // 莫队排序规则：左端点分块，偶数块升序、奇数块降序（奇偶优化，提速）
    bool operator<(const Query &other) const {
        if (l / block != other.l / block) 
            return l < other.l;
        return (l / block % 2 == 0) ? (r < other.r) : (r > other.r);
    }
} q[MAXN];

// 加入一个数字 x，O(1) 更新答案
void add(int x) {
    now -= 1LL * cnt[x] * cnt[x]; // 先减去旧平方
    cnt[x]++;                     // 次数+1
    now += 1LL * cnt[x] * cnt[x]; // 再加上新平方
}

// 删除一个数字 x，O(1) 更新答案
void del(int x) {
    now -= 1LL * cnt[x] * cnt[x]; // 先减去旧平方
    cnt[x]--;                     // 次数-1
    now += 1LL * cnt[x] * cnt[x]; // 再加上新平方
}

int main() {
    // 加速输入输出（洛谷必加，否则会超时）
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 1. 输入数据
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    // 2. 输入所有询问
    for (int i = 1; i <= m; i++) {
        cin >> q[i].l >> q[i].r;
        q[i].id = i; // 记录询问原始顺序
    }

    // 3. 初始化分块大小：根号n
    block = sqrt(n);

    // 4. 对询问排序（莫队核心）
    sort(q + 1, q + m + 1);

    // 5. 莫队双指针
    int l = 1, r = 0; // 初始区间为空
    for (int i = 1; i <= m; i++) {
        int ql = q[i].l; // 当前询问左端点
        int qr = q[i].r; // 当前询问右端点

        // 移动指针，调整到目标区间
        while (l > ql) add(a[--l]); // 左指针左移：加入元素
        while (r < qr) add(a[++r]); // 右指针右移：加入元素
        while (l < ql) del(a[l++]); // 左指针右移：删除元素
        while (r > qr) del(a[r--]); // 右指针左移：删除元素

        // 记录答案到原顺序位置
        ans[q[i].id] = now;
    }

    // 6. 按输入顺序输出答案
    for (int i = 1; i <= m; i++) {
        cout << ans[i] << '\n';
    }

    return 0;
}