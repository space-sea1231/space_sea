#include <bits/stdc++.h>
using namespace std;
using int64 = long long;

const int MAXN = 5000000;
int mu[MAXN + 5], prime[MAXN + 5];
bool vis[MAXN + 5];
int64 sumMu[MAXN + 5];
int64 sumMuK[MAXN + 5];

unordered_map<int64, int64> memoMu;
unordered_map<int64, int64> memoMuK;

// 线性筛预处理
void init(int n) {
    mu[1] = 1;
    int cnt = 0;
    for (int i = 2; i <= n; i++) {
        if (!vis[i]) {
            prime[++cnt] = i;
            mu[i] = -1;
        }
        for (int j = 1; j <= cnt && i * prime[j] <= n; j++) {
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0) {
                mu[i * prime[j]] = 0;
                break;
            } else {
                mu[i * prime[j]] = -mu[i];
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        sumMu[i] = sumMu[i - 1] + mu[i];
        sumMuK[i] = sumMuK[i - 1] + 1LL * mu[i] * i;
    }
}

// 杜教筛求 S_mu(n)
int64 getSumMu(int64 n) {
    if (n <= MAXN) return sumMu[n];
    if (memoMu.count(n)) return memoMu[n];
    
    int64 ans = 1;
    for (int64 l = 2, r; l <= n; l = r + 1) {
        r = n / (n / l);
        ans -= (r - l + 1) * getSumMu(n / l);
    }
    memoMu[n] = ans;
    return ans;
}

// 杜教筛求 S_muK(n) = sum_{i=1}^n mu(i) * i
// 正确公式：S_f(n) = 1 - sum_{l=2}^n l * S_f(n/l)
int64 getSumMuK(int64 n) {
    if (n <= MAXN) return sumMuK[n];
    if (memoMuK.count(n)) return memoMuK[n];
    
    int64 ans = 1;
    for (int64 l = 2, r; l <= n; l = r + 1) {
        r = n / (n / l);
        // sum_{i=l}^r i = (l + r) * (r - l + 1) / 2
        int64 sumG = (l + r) * (r - l + 1) / 2;
        ans -= sumG * getSumMuK(n / l);
    }
    memoMuK[n] = ans;
    return ans;
}

// 暴力验证函数（用于小数据测试）
int64 bruteForce(int64 a, int64 n) {
    int64 ans = 0;
    for (int64 k = 1; k <= n; k++) {
        int muK = 0;
        if (k <= MAXN) muK = mu[k];
        else {
            // 质因数分解求mu
            int64 x = k;
            int cnt = 0;
            bool sq = false;
            for (int64 i = 2; i * i <= x; i++) {
                if (x % i == 0) {
                    int c = 0;
                    while (x % i == 0) {
                        x /= i;
                        c++;
                        if (c >= 2) { sq = true; break; }
                    }
                    if (sq) break;
                    cnt++;
                }
            }
            if (!sq) {
                if (x > 1) cnt++;
                muK = (cnt % 2 == 0) ? 1 : -1;
            }
        }
        ans += muK * (a % k);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    init(MAXN);
    
    // 测试模式（可选）
    // 可以用小数据验证公式正确性
    
    while (t--) {
        int64 a, n;
        cin >> a >> n;
        
        // 使用恒等式：
        // sum_{k=1}^n mu(k) * (a mod k) 
        // = a * sum_{k=1}^n mu(k) - sum_{k=1}^n mu(k) * k * floor(a/k)
        
        int64 sumMuN = getSumMu(n);
        int64 ans = a * sumMuN;
        
        // 计算 sub = sum_{k=1}^n mu(k) * k * floor(a/k)
        int64 sub = 0;
        for (int64 l = 1, r; l <= n; l = r + 1) {
            if (a / l == 0) break;
            r = min(n, a / (a / l));
            
            // 计算 sum_{k=l}^r mu(k) * k
            int64 sumMuKBlock = getSumMuK(r) - getSumMuK(l - 1);
            sub += sumMuKBlock * (a / l);
        }
        
        ans -= sub;
        cout << ans << endl;
        
        // 调试：用小数据验证
        // if (n <= 1000) {
        //     int64 brute = bruteForce(a, n);
        //     if (ans != brute) {
        //         cerr << "WA! a=" << a << " n=" << n << " ans=" << ans << " brute=" << brute << endl;
        //     }
        // }
    }
    return 0;
}