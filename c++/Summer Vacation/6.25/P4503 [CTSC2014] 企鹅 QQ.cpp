#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <map>
#include <vector>
using namespace std;
typedef long long ll;

const int N = 3e4 + 10;
const int base1 = 131;
const int base2 = 233;
const int Mod1 = 1000000007;  // 1e9+7
const int Mod2 = 1000000009;  // 1e9+9

int n, l, m;
string s[N];
int hsh1[N], hsh2[N];
int pow1[N], pow2[N];

// 用 vector 代替大数组，只存储出现过的哈希值
vector<pair<int,int>> vec;
int tot1[N], tot2[N];  // 复用数组

int Hash1(string s) {
    ll sum = 0;
    for (int i = 0; i < s.size(); i++) 
        sum = (sum * base1 + (unsigned char)s[i]) % Mod1;
    return (int)sum;
}

int Hash2(string s) {
    ll sum = 0;
    for (int i = 0; i < s.size(); i++) 
        sum = (sum * base2 + (unsigned char)s[i]) % Mod2;
    return (int)sum;
}

signed main() {
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n >> l >> m;
    
    // 预处理幂次
    pow1[0] = pow2[0] = 1;
    for (int i = 1; i <= l; i++) {
        pow1[i] = (ll)pow1[i-1] * base1 % Mod1;
        pow2[i] = (ll)pow2[i-1] * base2 % Mod2;
    }
    
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
        hsh1[i] = Hash1(s[i]);
        hsh2[i] = Hash2(s[i]);
    }
    
    ll ans = 0;
    for (int i = 0; i < l; i++) {
        vec.clear();
        
        for (int j = 1; j <= n; j++) {
            // 计算去掉第 i 个字符后的哈希值
            ll sub1 = (ll)(unsigned char)s[j][i] * pow1[l - i - 1] % Mod1;
            ll sub2 = (ll)(unsigned char)s[j][i] * pow2[l - i - 1] % Mod2;
            
            int tmp1 = (hsh1[j] - sub1 + Mod1) % Mod1;
            int tmp2 = (hsh2[j] - sub2 + Mod2) % Mod2;
            
            vec.push_back({tmp1, tmp2});
        }
        
        // 排序统计
        sort(vec.begin(), vec.end());
        
        int cnt = 1;
        for (int j = 1; j < vec.size(); j++) {
            if (vec[j] == vec[j-1]) {
                cnt++;
            } else {
                ans += (ll)cnt * (cnt - 1) / 2;  // C(cnt, 2)
                cnt = 1;
            }
        }
        ans += (ll)cnt * (cnt - 1) / 2;
    }
    
    printf("%lld\n", ans);
    return 0;
}