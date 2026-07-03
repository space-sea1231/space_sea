#include <bits/stdc++.h>
using namespace std;

const int N = 1000005;
const int Mod = 998244353;
long long a[N];
int main() {
    int n;
    cin >> n;n++;
    for (int i = 1; i <= n; i++) a[i] = 1;
    for (int j = 2; j <= n; j++) {
        for (int i = j + 1; i <= n; i += j) {
            a[i] = (a[i] + a[j]) % Mod;
        }
    }
    for (int i = 2; i <= n; i++) printf("%d ", a[i]);
    
    return 0;
}