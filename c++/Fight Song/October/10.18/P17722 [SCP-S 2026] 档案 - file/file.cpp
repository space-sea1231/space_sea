#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define __Debug
#define Debug(x) cerr << #x << "=" << x << endl;

using namespace std;
typedef long long ll;

const int INF = sizeof(int) == 4 ? (int)1e9 + 1 : (int)1e18 + 1;
const int N = 2e6 + 10;

int n, m;
int a[N];
ll sum[N];

signed main() {
	cin.tie(nullptr) -> ios::sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> a[i];
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= m; i++) {
		int l;
		cin >> l;
		for (int j = 1; j <= l; j++) {
			int x;
			cin >> x;
			int pos = upper_bound(a + 1, a + n + 1, x) - a;
			// printf("%d %d\n", x, pos);
			sum[i] += n - pos + 1;
		}
		// printf("sum[%d]=%d\n", i, sum[i]);
	}
	sort(sum + 1, sum + m + 1);
	ll ans = 0;
	for (int i = 1; i <= m; i++) ans += ((m - i + 1) * sum[i]);
	printf("%lld\n", ans + (ll)m * n * (n + 1) / 2);
	return 0;
}
/*
You were the shadow to my life
Did you feel us
Another start
You fade away
Afraid our aim is out of sight
Wanna see us
Alive
Where are you now
Where are you now
Where are you now
Was it all in my fantasy
Where are you now
Were you only imaginary
Where are you now
Atlantis
Under the sea
Under the sea
Where are you now
Another dream
The monster's running wild inside of me
I'm faded
I'm faded
So lost I'm faded
I'm faded
So lost I'm faded
These shallow waters never met
What I needed
I'm letting go
A deeper dive
Eternal silence of the sea
I'm breathing
Alive
Where are you now
Where are you now
Under the bright
But faded lights
You set my heart on fire
Where are you now
Where are you now
Another dream
Another dream
Another dream
Another dream
Where are you now
Atlantis
Under the sea
Under the sea
Where are you now
Another dream
The monster's running wild inside of me
I'm faded
I'm faded
So lost I'm faded
I'm faded
So lost I'm faded [4]
*/