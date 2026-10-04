#include <bits/stdc++.h>
using namespace std;

static constexpr long long MOD = 1'000'000'007;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    // 按需预处理 2 的幂，避免每组数据重复快速幂。
    vector<long long> pow2 = {1};

    while (T--) {
        int n, k;
        string s;
        cin >> n >> k >> s;

        int r = 0;
        for (int i = static_cast<int>(s.size()) - 1;
             i >= 0 && s[i] == '0'; --i) {
            ++r;
        }

        if (r < k) {
            cout << 0 << '\n';
            continue;
        }

        while (static_cast<int>(pow2.size()) <= r + 1) {
            pow2.push_back(pow2.back() * 2 % MOD);
        }

        long long answer = (pow2[r + 1] - pow2[k] + MOD) % MOD;
        cout << answer << '\n';
    }

    return 0;
}