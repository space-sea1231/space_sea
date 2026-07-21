#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    while (T--)
    {
        ll k;
        cin >> k;
        ll lo = 1, hi = 100000;
        while (lo < hi)
        {
            ll mid = (lo + hi + 1) >> 1;
            if (mid * (mid - 1) / 2 <= k)
                lo = mid;
            else
                hi = mid - 1;
        }
        int ac = (int)lo, bc = (int)(k - lo * (lo - 1) / 2);
        cout << ac + bc << " 2" << endl;
        for (int i = 0; i < ac; ++i)
            cout << 'a';
        for (int i = 0; i < bc; ++i)
            cout << 'b';
        cout << endl;
    }
    return 0;
}
