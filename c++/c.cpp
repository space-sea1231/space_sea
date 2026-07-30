#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 10;
int T;
int n, top;
int cnt[N], b[N << 2];
bool Cmp(int x, int y) {
    int dx = min(x, n - x + 1);
    int dy = min(y, n - y + 1);
    if (dx != dy) return dx < dy;
    return x < y;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> T;
    while (T--) {
        cin >> n;
        int m = (n + 1) / 2;
        int total = n + m;
        vector<int> a;
        set<int> st;
		top = 0;
        for (int i = 1; i <= n; i++) cnt[i] = -1;
        for (int i = 1; i <= total; i++) {
            int x;
            cin >> x;
            cnt[x]++; b[i] = 0;
        }
        for (int i = 1; i <= n; i++) {
            for (int k = 1; k <= cnt[i]; k++) {
				b[top++] = i;
			}
        }
        sort(b, b + top, Cmp);
        for (int i = 1; i <= n; i++) st.insert(i);
        // a.reserve(n);
        a.push_back(b[0]);
        st.erase(b[0]);
		// cerr<<b[0] <<endl;
        for (int i = 1; i < m; i++) {
            int y = b[i];
            int siz = i - ((y - 1) - distance(st.begin(), st.lower_bound(y)));
            cerr<<*st.lower_bound(y) << " " << distance(st.begin(), st.lower_bound(y)) << endl;
			vector<int> par;
            if (st.count(y)) {
                par.push_back(y);
                st.erase(y);
            }
            for (int j = 1; j <= siz; j++) {
                auto it = st.begin();
                par.push_back(*it);
                st.erase(it);
            }
            while (par.size() < 2) {
                auto it = st.upper_bound(y);
                par.push_back(*it);
                st.erase(it);
            }
            a.push_back(par[0]); a.push_back(par[1]);
        }
        for (int i = 0; i < n; i++) printf("%d ", a[i]);
        printf("\n");
    }

    return 0;
}
/*
int cnt1[N];
vector<int> a;

bool Check() {
	priority_queue<int> maxHeap;  
	priority_queue<int, vector<int>, greater<int>> minHeap;
	for (int i = 1; i <= n; i++) cnt1[i] = 0;
	for (int i = 0; i < n; i++) {
		if (maxHeap.empty() || a[i] <= maxHeap.top()) {
			maxHeap.push(a[i]);
		} else {
			minHeap.push(a[i]);
		}
		
		if (maxHeap.size() > minHeap.size() + 1) {
			minHeap.push(maxHeap.top());
			maxHeap.pop();
		} else if (minHeap.size() > maxHeap.size()) {
			maxHeap.push(minHeap.top());
			minHeap.pop();
		}
		if (i % 2 == 0) cnt1[maxHeap.top()]++;
	}
	for (int i = 1; i <= n; i++) {
		// printf("%d %d %d\n", i, cnt1[i], cnt[i]);
		if (cnt1[i] != cnt[i]) return false;
	}
	return true;
}
*/