#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <chrono>
#include <random>
#include <set>
#include <queue>

using namespace std;
typedef long long ll;

int t = 1;
int n = 100009;
int a[300000 + 10];
set<int> st;
mt19937 Rand(chrono::steady_clock().now().time_since_epoch().count());
int Random(int l, int r) {
	return Rand() % (r - l + 1) + l;
}
int main() {
    srand((unsigned)time(0));
    printf("%d\n", t);
    while (t--) {
        printf("%d\n", n);
        for (int i = 1; i <= n; i++) a[i] = i;
        for (int i = 1; i <= n; i++) {
            int x = Random(1, n);
            int y = Random(1, n);
            swap(a[x], a[y]);
        }
        priority_queue<int> maxHeap;  // 大根堆，存较小的一半
        priority_queue<int, vector<int>, greater<int>> minHeap;  // 小根堆，存较大的一半
        for (int i = 1; i <= n; i++) printf("%d ", a[i]);
        for (int i = 1; i <= n; i++) {
        // 插入当前元素
            if (maxHeap.empty() || a[i] <= maxHeap.top()) {
                maxHeap.push(a[i]);
            } else {
                minHeap.push(a[i]);
            }
            
            // 平衡两个堆
            if (maxHeap.size() > minHeap.size() + 1) {
                minHeap.push(maxHeap.top());
                maxHeap.pop();
            } else if (minHeap.size() > maxHeap.size()) {
                maxHeap.push(minHeap.top());
                minHeap.pop();
            }
            
            // 长度为奇数时输出中位数
            if (i % 2 == 1) {
                cout << maxHeap.top() << " ";
            }
        }

    }
    return 0;
}