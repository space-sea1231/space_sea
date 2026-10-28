#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#include <stack>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e3 + 10;

int n;
int a[N];
int minn[N];
bool color[N];
bool vis[N];
bool flag;

vector<int> e[N];

void Dfs(int u, int fa) {
    vis[u] = true;
    color[u] = color[fa] ^ 1;
    for (int v : e[u]) {
        if (v == fa) continue;
        if (vis[v]) {
            if (color[u] == color[v]) flag = true;
            continue;
        }
        Dfs(v, u);
    }
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    minn[n + 1] = INF; color[0] = true;

    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = n; i; i--) minn[i] = min(minn[i + 1], a[i]);
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (minn[j + 1] < a[i] && a[i] < a[j]) {
                e[i].emplace_back(j);
                e[j].emplace_back(i);
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            Dfs(i, 0);
        }
    }
    if (flag) { printf("0\n"); return 0; }
    stack<int> A, B;
    int lst = 0;
    for (int i = 1; i <= n; i++) {
        if (!color[i]) {
            while (!A.empty() && A.top() < a[i]) {
                while (!B.empty() && B.top() < A.top()) {
                    B.pop();
                    printf("d ");
                    lst++;
                }
                A.pop();
                printf("b ");
                lst++;
            }
            A.push(a[i]);
            printf("a ");
        } else {
            while (!A.empty() && A.top() == lst + 1) {
                A.pop();
                lst++;
                printf("b ");
            }
            while (!B.empty() && B.top() < a[i]) {
                while (!A.empty() && A.top() < B.top()) {
                    A.pop();
                    printf("b ");
                    lst++;
                }
                B.pop();
                printf("d ");
                lst++;
            }
            while (!A.empty() && A.top() == lst + 1) {
                A.pop();
                lst++;
                printf("b ");
            }
            B.push(a[i]);
            printf("c ");
        }
    }
    while (!A.empty() || !B.empty()) {
        if (A.empty()) {
            B.pop();
            printf("d ");
        } else if (B.empty()) {
            A.pop();
            printf("b ");
        } else if (A.top() < B.top()) {
            A.pop();
            printf("b ");
        } else {
            B.pop();
            printf("d ");
        }
    }
    return 0;
}