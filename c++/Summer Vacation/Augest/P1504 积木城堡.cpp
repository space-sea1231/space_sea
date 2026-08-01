#include <bits/stdc++.h>
using namespace std;
const int N = 1e4 + 10;
int n, num, sum, maxn;
int cnt[N];
bool dp[N];
int main() {
    cin >> n;
    for (int k = 1; k <= n; k++) {
		vector<int> a;
        memset(dp, 0, sizeof(dp));
        num=sum=0;
        dp[0]=true;
		while (1) {
			int x;
			cin >> x;
			if (x == -1) break;
			a.emplace_back(x);
			sum += x;
		}
		int n = a.size();
        maxn=max(maxn, sum);
        for(auto x:a){
            for(int i=sum; i>=x; i--){
				// printf("dp[%d]=%d dp[%d]=%d\n", i, dp[i], i - x, dp[i - x]);
				dp[i]|=dp[i-x];
				// printf("dp[%d]=%d dp[%d]=%d\n", i, dp[i], i - x, dp[i - x]);

            }
        }
		for (int i = 0; i <= sum; i++) cnt[i] += (int)dp[i];
    }
    for (; maxn>=0; maxn--){
    	if(cnt[maxn]==n){
    		break;
    		
		}
	}
    cout << maxn;
    
    return 0;
}