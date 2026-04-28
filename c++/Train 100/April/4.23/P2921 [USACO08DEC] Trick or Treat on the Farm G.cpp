#include <iostream>
#include <stdio.h>
#include <stack>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 1e5 + 10;

int n;
int to[N];
int len[N];
int sum[N];
int ans[N];
stack<int> q;

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> to[i];
    for (int i = 1; i <= n; i++) {
        if (!ans[i]) {
            int cur = i, cnt = 0;
            q.push(cur);
            sum[cur] = ++cnt;
            while (1) {
                cur = to[cur];
                cnt++;
                if (ans[cur]) {
                    while (!q.empty()) {
                        int now = q.top();
                        q.pop();
                        ans[now] = ans[cur] + cnt - sum[now];
                    }
                    break;
                }
                if (sum[cur]) {
                    bool flag = false;
                    while (!q.empty()) {
                        int now = q.top();
                        q.pop();
                        if (flag) ans[now] = cnt - sum[now];
                        else {
                            ans[now] = len[now] = cnt - sum[cur];
                            flag |= (now == cur);
                        }
                    }
                    break;
                }
                else {
                    sum[cur] = cnt;
                    q.push(cur);
                }
            }
        }
    }
    for (int i = 1; i <= n; i++) printf("%d\n", ans[i]);
    return 0;
}