#include <iostream>
#include <stdio.h>
#include <algorithm>
#define __Debug

using namespace std;
typedef long long ll;

const int N = 1e2 + 10;
const int INF = 0x3f3f3f3f;

int n, m;
int v[N], p[N];
int pos1[N], pos2[N], pos3[N], pos4[N];
int sum1[N], sum2[N], sum3[N], sum4[N];
int top1, top2, top3, top4;

bool Cmp(int srca, int srcb) {
    return p[srca] > p[srcb];
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> m;
    int minn = INF;
    for (int i = 1; i <= n; i++) {
        cin >> v[i] >> p[i];
        minn = min(minn, v[i]);
    }
    for (int i = 1; i <= n; i++) {
        if (v[i] - minn == 0) pos1[++top1] = i;
        if (v[i] - minn == 1) pos2[++top2] = i;
        if (v[i] - minn == 2) pos3[++top3] = i;
        if (v[i] - minn == 3) pos4[++top4] = i;
    }
    sort(pos1 + 1, pos1 + top1 + 1, Cmp);
    sort(pos2 + 1, pos2 + top2 + 1, Cmp);
    sort(pos3 + 1, pos3 + top3 + 1, Cmp);
    sort(pos4 + 1, pos4 + top4 + 1, Cmp);
    for (int i = 1; i <= top1; i++) sum1[i] = sum1[i - 1] + p[pos1[i]];
    for (int i = 1; i <= top2; i++) sum2[i] = sum2[i - 1] + p[pos2[i]];
    for (int i = 1; i <= top3; i++) sum3[i] = sum3[i - 1] + p[pos3[i]];
    for (int i = 1; i <= top4; i++) sum4[i] = sum4[i - 1] + p[pos4[i]];
    int ans = 0;
    for (int i = 0; i <= top1; i++) {
        for (int j = 0; j <= top2; j++) {
            for (int k = 0; k <= top3; k++) {
                int tmp = i * minn + j * (minn + 1) + k * (minn + 2);
                if (tmp <= m) {
                    int l = (m - tmp) / (minn + 3);
                    ans = max(ans, sum1[i] + sum2[j] + sum3[k] + sum4[l]);
                }
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}