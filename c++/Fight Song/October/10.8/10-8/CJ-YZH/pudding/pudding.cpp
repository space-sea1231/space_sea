#include <bits/stdc++.h>
using namespace std;

typedef long long ll; 

vector<ll> vec;

vector<ll> Query(ll mx) {
    ll lim = sqrtl((long double)mx);

    while (lim + 1 <= mx / (lim + 1)) ++lim;
    while (lim > mx / lim) --lim;

    vector<bool> composite(lim + 1, false);
    for (ll i = 2; i <= lim / i; ++i) {
        if (!composite[i]) {
            for (ll j = i * i; j <= lim; j += i) {
                composite[j] = true;
            }
        }
    }

    vector<ll> primes;
    for (ll i = 2; i <= lim; ++i) {
        if (!composite[i]) primes.push_back(i);
    }
    return primes;
}

ll Calc2(ll L, ll R) {
    if (R < 3) return 0;

    L = max<ll>(L, 3);
    if ((L & 1) == 0) ++L;  
    if (L > R) return 0;

    vector<bool> composite((R - L) / 2 + 1, false);

    for (ll p : vec) {
        if (p > R / p) break;  
        if (p == 2) continue;   

        ll first = (L / p) * p;
        if (first < L) {
            if (first > R - p) continue;
            first += p;
        }

        ll pp = p * p;
        if (first < pp) first = pp; 

        if ((first & 1) == 0) {
            if (first > R - p) continue;
            first += p;
        }

        ll step = 2 * p;
        for (ll x = first; x <= R; ) {
            composite[(x - L) / 2] = true;
            if (x > R - step) break;
            x += step;
        }
    }

    ll ans = 0;
    for (bool x : composite) {
        if (!x) ++ans;
    }
    return ans;
}

ll Calc1(ll x) {
    if (x <= 0) return 0;
    return x / 4 + (x % 4 >= 2);
}

int main() {
    freopen("pudding.in", "r", stdin);
    freopen("pudding.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    vector<pair<ll, ll>> queries(t);
    ll maxR = 1;

    for (int i = 0; i < t; ++i) {
        ll l, r;
        cin >> l >> r;
        queries[i] = {l, r};
        maxR = max(maxR, r);
    }

    vec = Query(maxR);

    for (auto [l, r] : queries) {
        ll ans = 0;

        ans += Calc1(r) - Calc1(l - 1);

        ans += Calc2(l, r);

        ll L4 = l / 4 + (l % 4 != 0); 
        ll R4 = r / 4;               
        ans += Calc2(L4, R4);

        if (l <= 1 && 1 <= r) ++ans;
        if (l <= 4 && 4 <= r) ++ans;
        if (l <= 8 && 8 <= r) ++ans;

        cout << ans << '\n';
    }

    return 0;
}