#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

// 你可以自由修改这两个参数控制数据大小
const int MAX_N = 10;  // 序列长度
const int MAX_M = 200;  // 操作次数

int randint(int l, int r) {
    return (long long)rand() * rand() % (r - l + 1) + l;
}

int main() {
    srand((unsigned)time(0));
    
    int n = MAX_N;
    int m = MAX_M;
    printf("%d %d\n", n, m);
    
    // 生成初始 0/1 序列
    for (int i = 1; i <= n; ++i) {
        printf("%d ", randint(0, 1));
    }
    puts("");
    
    // 生成 m 个操作（5 种操作均匀随机）
    for (int i = 1; i <= m; ++i) {
        int op = randint(0, 4);
        int l = randint(1, n);
        int r = randint(1, n);
        if (l > r) swap(l, r);
        printf("%d %d %d\n", op, l - 1, r - 1); 
        // 重要：这题输入 l,r 是 0 下标！！！
    }
    return 0;
}