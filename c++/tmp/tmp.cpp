#pragma GCC optimize("O3,unroll-loops")
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 100005;      // 最大点数
const int M = 300005;      // 最大边数

// ============================================================
// 核心数据结构：动态并查集森林
// p[u][k] 表示节点 u 在第 k 层森林中的父节点
// sz[u][k] 表示节点 u 在第 k 层森林中的子树大小
// ============================================================
vector<int> p[N];
vector<int> sz[N];

int ans[M];                // ans[i] = 边 i 被分配到的森林层数（从0开始）
int edges_in_forest[M];    // edges_in_forest[k] = 第 k 层森林中有多少条边

// ============================================================
// 路径压缩：查找节点 u 在第 k 层森林中的根节点
// ============================================================
int get_p(int u, int k) {
    // 如果该节点在第 k 层还没有父节点记录，说明它是孤立的根
    if (k >= (int)p[u].size()) return u;
    
    // 如果自己是自己的父节点，就是根
    if (p[u][k] == u) return u;
    
    // 路径压缩：递归查找父节点的根，并直接挂到根上
    return p[u][k] = get_p(p[u][k], k);
}

void solve() {
    int n, m;
    cin >> n >> m;
    
    // 清空上一组数据
    for (int i = 1; i <= n; i++) {
        p[i].clear();
        sz[i].clear();
    }
    
    int max_k = -1;          // 当前使用到的最大层数
    
    // ============================================================
    // 逐条处理边，边权就是输入顺序 i
    // ============================================================
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        
        // ============================================================
        // 二分查找：找到最小的 k，使得在 Forest k 中 u 和 v 不连通
        // 这个 k 就是这条边的归属层
        // 性质：如果 u,v 在 Forest k 中连通，则在 Forest k+1 中也连通
        // 所以连通性在 k 上是单调的，可以二分
        // ============================================================
        int low = 0, high = max_k;
        int target_k = max_k + 1;   // 默认放到最新一层
        
        while (low <= high) {
            int mid = low + (high - low) / 2;
            
            if (get_p(u, mid) == get_p(v, mid)) {
                // 在 mid 层已经连通 → 这条边放进去会成环
                // 所以需要放到更深的层（更大的 k）
                low = mid + 1;
            } else {
                // 在 mid 层不连通 → 可以放在这一层或更浅的层
                target_k = mid;
                high = mid - 1;
            }
        }
        
        // ============================================================
        // 在 target_k 层中合并 u 和 v
        // ============================================================
        int pu = get_p(u, target_k);
        int pv = get_p(v, target_k);
        
        if (pu != pv) {
            // 动态扩展 pu 的父节点数组，确保有 target_k 层
            while ((int)p[pu].size() <= target_k) {
                p[pu].push_back(pu);
                sz[pu].push_back(1);
            }
            // 动态扩展 pv 的父节点数组，确保有 target_k 层
            while ((int)p[pv].size() <= target_k) {
                p[pv].push_back(pv);
                sz[pv].push_back(1);
            }
            
            // 按大小合并（启发式合并），保证并查集树高度 O(log n)
            if (sz[pu][target_k] < sz[pv][target_k]) {
                swap(pu, pv);
            }
            
            // 把 pv 的根指向 pu
            p[pv][target_k] = pu;
            sz[pu][target_k] += sz[pv][target_k];
        }
        
        // ============================================================
        // 记录这条边的归属层
        // ============================================================
        ans[i] = target_k;
        edges_in_forest[target_k]++;    // 该层森林边数 +1
        max_k = max(max_k, target_k);   // 更新最大层数
    }
    
    // ============================================================
    // 计算有多少层森林是完整的 MST（边数 = n-1）
    // K_full 表示完整的森林层数
    // ============================================================
    int K_full = 0;
    while (K_full <= max_k && edges_in_forest[K_full] == n - 1) {
        K_full++;
    }
    
    // ============================================================
    // 输出答案
    // 如果 ans[i] < K_full：边在第 ans[i] 层森林中被删除
    // 否则：操作结束时未被删除 → -1
    // ============================================================
    for (int i = 1; i <= m; i++) {
        if (ans[i] < K_full) {
            cout << ans[i] + 1;   // 层数从0开始，所以 +1
        } else {
            cout << -1;
        }
        if (i != m) cout << " ";
    }
    cout << "\n";
    
    // 清空 edges_in_forest 数组（只清理用到的层，O(K) 而不是 O(M)）
    for (int i = 0; i <= max_k + 1; i++) {
        edges_in_forest[i] = 0;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    if (cin >> t) {
        while (t--) solve();
    }
    return 0;
}