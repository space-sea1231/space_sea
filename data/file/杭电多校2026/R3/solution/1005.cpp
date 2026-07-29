#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6+20;
vector<int> p;
void sieve(){
    static bool vis[N];
    for(int i = 2; i < N; i++){
        if(!vis[i]){
            p.push_back(i);
            for(ll j = 1ll * i * i; j < N; j += i) vis[j] = true;
        }
    }
}
int solve(ll x){
    if(x == 1) return 0;
    int ans = 0;
    for(int i: p){
        int c = 0;
        while(x % i == 0) c++, x /= i;
        ans = max(ans, (int)log2(c) + 1);
    }
    if(x > 1){
        ll y = sqrt(x);
        if(y * y == x || (y+1) * (y+1) == x) ans = max(ans, 2);
        else ans = max(ans, 1);
    }
    return ans; 
}
int main(){
    sieve();
    int _; cin >> _;
    while(_--){
        ll x; cin >> x;
        cout << solve(x) << endl;
    }
    return 0;
}