/*******************************************************
Author: kkksc0114514
File name: wo.cpp
Time: 2024.10.17 07:57
Pay attention to your academic integrity!
********************************************************/
#include <bits/stdc++.h>
namespace SXL {
    constexpr int MAXN = 2e6 + 5,MOD = 998244353;
    int a[MAXN];
    int del[MAXN];
    void solve() {
        int n,ax = 0,bx = 0;
        scanf("%d",&n);
        int mid = 0,tmp = 0;
        for(int i = 1;i <= 2 * n;i++) {
            scanf("%d",a + i);
            if(a[i] != 0 && a[i + 1] != 0) {
                del[a[i]] = 1;
                del[a[i + 1]] = 1;
                continue;
            }
        }
        for(int i = 1;tmp < n;i++) {
            if(!del[i]) tmp++;
            if(tmp < n || (mid + 1) == i) mid++;
        }
        for(int i = 1;i <= n * 2;i += 2) {
            if(a[i] != 0 && a[i + 1] != 0) continue;
            if(a[i] == 0 && a[i + 1] != 0) a[i + 1] <= mid ? ++bx : ++ax;
            else if(a[i] != 0 && a[i + 1] == 0) a[i] <= mid ? ++bx : ++ax;
            else ax++,bx++;
        }
        int ans = 1;
        for(int i = 1;i <= n * 2;i += 2) {
            if(a[i] != 0 && a[i + 1] != 0) {
                continue;
            }
            if(a[i] == 0 && a[i + 1] != 0) {
                ans = (1LL * ans * (a[i + 1] <= mid ? bx : ax)) % MOD;
                a[i + 1] <= mid ? --bx : --ax;
            }
            else if(a[i] != 0 && a[i + 1] == 0) {
                ans = (1LL * ans * (a[i] <= mid ? bx : ax)) % MOD;
                a[i] <= mid ? --bx : --ax;
            }
            else {
                ans = (2LL * ans * ax * bx) % MOD;
                --bx;
                --ax;
            }
        }
        printf("%d\n",ans);
    }
    void main() {
        int t;
        scanf("%d",&t);
        while(t--) {
            solve();
        }
    }
} // namespace SXL
int main() {
    freopen("wo.in","r",stdin);
    freopen("wo.out","w",stdout);
    SXL::main();
    return 0;
}