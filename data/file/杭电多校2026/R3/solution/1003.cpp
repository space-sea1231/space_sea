#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+10;
typedef long long ll;
inline ll read(){
    char ch = getchar();
    while(!isdigit(ch)) ch = getchar();
    ll ans = 0;
    while (isdigit(ch)) ans = ans * 10 + ch - '0', ch = getchar();
    return ans;
}
int n;
ll a[N];
ll solve(){
    static ll f[62];
    for(int i = 0; i <= 61; i ++) f[i] = LLONG_MAX;
    f[0] = 0;
    for(int i = 1; i <= n; i++){
        for(int j = 61; j >= 1; j--){
            if(f[j-1] <= a[i]) f[j] = min(f[j], f[j-1] + a[i]);
        }
    }
    for(int i = 61; i >= 0; i--) if(f[i] < LLONG_MAX) return i;
    return -1;
}
int main(){
    int _ = read();
    while(_--){
        n = read();
        for(int i = 1; i <= n; i++) a[i] = read();
        cout << solve() << '\n';
    }
    return 0;
}