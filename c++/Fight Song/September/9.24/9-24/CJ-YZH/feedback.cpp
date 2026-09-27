#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <vector>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 1e6 + 10;

int n;
int a[N];
ll sum[N];
char ansc[N];
bool flag[N];
vector<pair<int, int> > q;

signed main() {
    freopen("feedback.in", "r", stdin);
    freopen("feedback.out", "w", stdout);
    cin.tie(nullptr) -> ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    int l = 1, r = 0;
    for (int i = 1; i <= n; i++) {
        char c;
        cin >> c;
        // cerr << c << " ";
        flag[i] = (c == 'G' ? 1 : 0);
    }
    for (int i = 1; i <= n; i++) {
        if (flag[i] != flag[i + 1] || i == n) {
            q.emplace_back(make_pair(l, i));
            l = i + 1;
        }
    }
    // for (int i = 0; i < q.size(); i++) printf("%d %d\n", q[i].first, q[i].second);
    sort(a + 1, a + n + 1);
    ll tot = 0;
    for (int i = 1; i <= n; i++) sum[i] = sum[i - 1] + a[i];
    for (int i = 0, siz = q.size(); i < siz - 1; i++) {
        int l = q[i].first, r = q[i].second;
        if (flag[l]) { // 
            int ans = l;
            int ll = l, rr = r;
            while (ll <= rr) {
                int mid = ll + rr >> 1;
                if (abs(tot + sum[mid] - sum[l - 1]) < sum[r] - sum[mid] + a[q[i + 1].first]) {
                    ans = mid;
                    ll = mid + 1;
                } else rr = mid - 1;
            }
            if (abs(tot + sum[ans] - sum[l - 1]) < sum[r] - sum[ans] + a[q[i + 1].first]) {
                // if (q[i].first == 3) {
                //     cerr << "ans = " << ans << " tot = " << tot << endl;
                //     cerr << abs(tot + sum[ans] - sum[l - 1]) << " " << sum[r] - sum[ans] + a[q[i + 1].first];
                // }
                for (int j = q[i].first; j <= ans; j++) {
                    tot += a[j];
                    ansc[j] = 'G';
                }
                for (int j = ans + 1; j <= q[i].second; j++) {
                    tot -= a[j];
                    ansc[j] = 'B';
                }
            } else {
                ans = l;
                int ll = l, rr = r;
                while (ll <= rr) {
                    int mid = ll + rr >> 1;
                    if (abs(tot + sum[r] - sum[mid]) < sum[mid] - sum[l - 1] + a[q[i + 1].first]) {
                        ans = mid;
                        rr = mid - 1;
                    } else ll = mid + 1;
                }
                for (int j = q[i].first; j <= ans; j++) {
                    tot -= a[j];
                    ansc[j] = 'B';
                }
                for (int j = ans + 1; j <= q[i].second; j++) {
                    tot += a[j];
                    ansc[j] = 'G';
                }
            }
        } else {
            int ans = l;
            int ll = l, rr = r;
            while (ll <= rr) {
                int mid = ll + rr >> 1;
                if (abs(tot - (sum[mid] - sum[l - 1])) < sum[r] - sum[mid] + a[q[i + 1].first]) {
                    ans = mid;
                    ll = mid + 1;
                } else rr = mid - 1;
            }
            if (abs(tot - (sum[ans] - sum[l - 1])) < sum[r] - sum[ans] + a[q[i + 1].first]) {
                for (int j = q[i].first; j <= ans; j++) {
                    tot -= a[j];
                    ansc[j] = 'B';
                }
                for (int j = ans + 1; j <= q[i].second; j++) {
                    tot += a[j];
                    ansc[j] = 'G';
                }
            } else {
                ans = l;
                int ll = l, rr = r;
                while (ll <= rr) {
                    int mid = ll + rr >> 1;
                    if (abs(tot - (sum[r] - sum[mid])) < sum[mid] - sum[l - 1] + a[q[i + 1].first]) {
                        ans = mid;
                        rr = mid - 1;
                    } else ll = mid + 1;
                }
                for (int j = q[i].first; j <= ans; j++) {
                    tot += a[j];
                    ansc[j] = 'G';
                }
                for (int j = ans + 1; j <= q[i].second; j++) {
                    tot -= a[j];
                    ansc[j] = 'B';
                }
            }
        }
        // if (q[i].first == 8) cerr<<"ddd:" << tot << endl;;
    }
    for (int i = q[q.size() - 1].first; i <= n; i++) ansc[i] = (flag[i] ? 'G' : 'B');
    for (int i = 1; i <= n; i++) printf("%d %c\n", a[i], ansc[i]);
    // ll ttt = 0;
    // for (int i = 1; i <= n; i++) printf("%c", ansc[i]);
    // for (int i = 1; i <= n; i++) {
    //     if (ansc[i] == 'G') ttt += a[i];
    //     else ttt -= a[i];
    //     if (ttt > 0 && flag[i] == 0) printf("My G:%d\n", i); 
    //     if (ttt < 0 && flag[i] == 1) printf("My B:%d\n", i); 
    // }
    return 0;
}