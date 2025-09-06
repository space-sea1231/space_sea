#include <bits/stdc++.h>
using namespace std;
int n , cnt0 = 0;
string s;
inline int calc (int x)
{
    while (x >= 3) x -= (x / 3) * 2;
    return x;
}
vector <int> ans;
inline void doit (int x)
{
    bool t1 = s[x - 1] - '0' , t2 = s[x] - '0' , t3 = s[x + 1] - '0';
    t1 = ((!t1) & (!t2)); t3 = ((!t2) & (!t3));
    s[x - 1] = t1 + '0' , s[x + 1] = t3 + '0';
    ans.push_back (x);
}
signed main ()
{
	freopen ("shi.in" , "r" , stdin);
	freopen ("shi.out" , "w" , stdout);
    ios::sync_with_stdio (0); cin.tie (0); cout.tie (0);
    int t; cin >> t;
    while (t--)
    {
        cin >> s; n = s.size (); ans.clear ();
        s = " " + s;
        int now = n ;
        for (int i = 1; i <= n; i++) if (s[i] == '0') {now = i; break;};
        while (now < n)
        {
            if (now >= 2 && s[now + 1] == '0' && s[now] == '0' && s[now - 1] == '0')
                doit (now);
            if (s[now + 1] == '0') now++;
            else if (now + 2 < n) doit (now + 2);
            else if (now + 2 == n && now >= 2 && s[now - 1] == '0') doit (now);
            else break;
            if (now + 1 == n && s[now + 1] == '1') break;
        }
        int res = 0;
        for (int i = 1; i <= n; i++) res += (s[i] == '1');
        cout << res << " " << ans.size () << "\n";
        for (auto i : ans) cout << i << " "; cout << "\n";
    }
	return 0;
}/*
10111110110111
 */
