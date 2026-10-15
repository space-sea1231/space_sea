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
const int N = 1e5 + 10;

int n;
int cnt;
int prime[N];
bool vis[N];

void Prime() {
    for (int i = 2; i < N; i++) {
        if (!vis[i]) prime[++cnt] = i;
        for (int j = 1; j <= cnt && i * prime[j] < N; j++) {
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0) continue;
        }
    }
}
int Calc(int x) {
    if (x <= 0) return 0;
    return x / 4 + (x % 4 >= 2);
}
int Screen(int l, int r) {
    if (r < 3) return 0;
    l = max(l, 3);
    if ((l & 1) == 0) l++;
    if (l > r) return 0;

    vector<bool> flag((r - l) / 2 + 1, false);
    for (int i = 1; i <= cnt; i++) {
        int p = prime[i];
        if ((ll)p * p > r) break;
        if (p == 2) continue;
        int st = (l / p) * p;
        if (st < l) {
            if (st > r - p) continue;
            st += p;
        }
        int pp = p * p;
        if (st < pp) st = pp; 
        if ((st & 1) == 0) {
            if (st > r - p) continue;
            st += p;
        }
        for (int i = st; i <= r; i += 2 * p) {
            // if ((i - l) / 2 > (r - l) / 2) cerr << (i - l) / 2 << " " << (r - l) / 2 << "\n";
            flag[(i - l) / 2] = true;
        }
    }
    int ans = 0;
    for (bool cur : flag) ans += (cur ^ 1);
    return ans;
}
signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    Prime();
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int l, r;
        cin >> l >> r;
        int ans = Calc(r) - Calc(l - 1);
        ans += Screen(l, r);
        ans += Screen(l / 4 + (l % 4 != 0), r / 4);

        if (l <= 1 && 1 <= r) ans++;
        if (l <= 4 && 4 <= r) ans++;
        if (l <= 8 && 8 <= r) ans++;
        printf("%d\n", ans);
    }
    return 0;
}
/*
AddressSanitizer:DEADLYSIGNAL
=================================================================
==432172==ERROR: AddressSanitizer: SEGV on unknown address 0x000000000000 (pc 0x556d99031653 bp 0x000000011431 sp 0x7fff0379f480 T0)
==432172==The signal is caused by a READ memory access.
==432172==Hint: address points to the zero page.
    #0 0x556d99031652 in std::_Bit_reference::operator=(bool) /usr/include/c++/9/bits/stl_bvector.h:93
    #1 0x556d99031652 in Screen(int, int) /home/space_sea/Caged_Gardenia/c++/std/std.cpp:48
    #2 0x556d9902fca0 in main /home/space_sea/Caged_Gardenia/c++/std/std.cpp:62
    #3 0x7f6a96e8d082 in __libc_start_main ../csu/libc-start.c:308
    #4 0x556d9903019d in _start (/tmp/cph-ng/std+0x519d)

AddressSanitizer can not provide additional info.
SUMMARY: AddressSanitizer: SEGV /usr/include/c++/9/bits/stl_bvector.h:93 in std::_Bit_reference::operator=(bool)
==432172==ABORTING
*/