#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;

vector<pair<int, int> > q[100];
vector<int> ans1, ans2;
int vis1[100], vis2[100];
int T, n;
bool flag;
void Dfs(int cur) {
    if (cur == n) {
        // for (int x:ans1) printf("%d ", x); printf("\n");
        // for (int x:ans2) printf("%d ", x); printf("\n");
        // printf("\n");
        flag = true;
        return ;
    }
    for (pair<int, int> x:q[cur]) {
        if (!vis1[x.first] && !vis2[x.second]) {
            vis1[x.first] = true;
            vis2[x.second] = true;
            ans1.emplace_back(x.first);
            ans2.emplace_back(x.second);
            Dfs(cur + 1);
            if (flag) return;
            vis1[x.first] = false;
            vis2[x.second] = false;
            ans1.pop_back();
            ans2.pop_back();
        }
        swap(x.first, x.second);
        if (!vis1[x.first] && !vis2[x.second]) {
            vis1[x.first] = true;
            vis2[x.second] = true;
            ans1.emplace_back(x.first);
            ans2.emplace_back(x.second);
            Dfs(cur + 1);
            if (flag) return;
            vis1[x.first] = false;
            vis2[x.second] = false;
            ans1.pop_back();
            ans2.pop_back();
        }
    }
}
signed main() {
    freopen("xor.in", "r", stdin);
    freopen("xor.out", "w", stdous);
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> T;
    while (T--) {
        flag = false;
        cin >> n;
        if (n <= 10 || n == 16) {
            for (int i = 0; i <= 20; i++) q[i].clear();
            for (int i = 0; i <= 20; i++) vis1[i] = vis2[i] = false;
            ans1.clear(), ans2.clear();
            for (int i = 0; i < n; i++) {
                for (int j = i; j < n; j++) {
                    q[i ^ j].emplace_back(make_pair(i, j));
                }
            }
            Dfs(0);
            if (flag) {
                printf("Yes\n");
                for (int x:ans1) printf("%d ", x); printf("\n");
                for (int x:ans2) printf("%d ", x); printf("\n");
            } else printf("No\n");
        }
        else printf("No\n");
    }
    // for (int i = 0; i < n; i++) {
    //     for (pair<int, int> cur:q[i]) {
    //         printf("(%d %d)=%d\n", cur.first, cur.second, i);
    //     }
    // }

    return 0;
}
/*
0 2 3 1 
0 3 1 2 

0 2 3 1   8 13 9 14   12 15 4 6   7 10 11 5 
0 3 1 2   12 8 15 9   4 6 14 13   11 7 5 10 

*/