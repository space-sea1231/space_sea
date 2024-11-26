#include <bits/stdc++.h>
constexpr int N = 1e6 + 5;

int main() {
    std::cin.tie(nullptr) -> sync_with_stdio(false);
    freopen("shi.in","r",stdin);
    freopen("shi.out","w",stdout);
    int T;
    auto solve = []() -> void {
        std::string s;
        std::cin >> s;
        int n = s.size();
        s = '#' + s;
        if (n <= 2)
            return std::cout << "0 0\n\n",void();
        else if (n == 3) {
            if (s == "000") 
                std::cout << "0 1\n2\n";
            else
                std::cout << "0 0\n\n";
            return;
        }
        std::vector<int> a(n+1), res;
        auto change = [&](int x) {
            a[x - 1] = !a[x - 1] & !a[x];
            a[x + 1] = !a[x + 1] & !a[x];
        };
        for (int i = 1; i <= n; ++i)
            a[i] = s[i] - '0';
        for (int i = 1; i <= n - 3; ++i) {
            if (!a[i]) {
                if (a[i + 1]) {
                    res.push_back(i + 2);
                    change(i + 2);
                }
                res.push_back(i + 1);
                change(i + 1);
            }
        }
        if (!a[n - 2] && !a[n - 1] && !a[n])
            res.push_back(n - 1);
        std::cout << "0 " << res.size() << '\n';
        for(int x : res)
            std::cout << x << ' ';
        std::cout << '\n';
        return;
    };
    for(std::cin >> T; T; --T) solve();
    return 0;
}