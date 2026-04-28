#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 5e5 + 10;
int n, m;

namespace BinaryTree {
    int sum[N];
    
    int Lowbit(int x) {
        return x & -x;
    }
    void Add(int x, int val) {
        for (int i = x; i <= n; i += Lowbit(i)) sum[i] += val;
        return;
    }
    int Query(int x) {
        int rev = 0;
        for (int i = x; i >= 1; i -= Lowbit(i)) rev += sum[i];
        return rev; 
    }
}using namespace BinaryTree;
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        Add(i, a);
    }
    for (int i = 1; i <= m; i++) {
        int opt, x, y;
        cin >> opt >> x >> y;
        if (opt == 1) Add(x, y);
        if (opt == 2) printf("%d\n", Query(y) - Query(x - 1));
    }
    return 0;
}