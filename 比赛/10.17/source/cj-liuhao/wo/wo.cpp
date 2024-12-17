#include <bits/stdc++.h>
using namespace std;
#define int long long

namespace mci {
	const int mod=998244353;
	int t,n;
	array<int,1919810> a;
	
	int main () {
		cin>> t;
		while (t--) {
			cin>> n;
			int lhs=n,rhs=n;
			for (int i=1;i<=n*2;i++) {
				cin>> a[i];
				lhs-=(a[i]&&a[i]<=n);
				rhs-=(a[i]&&a[i]>n);
			}
			int ans=1;
			for (int i=1;i<=n;i++) {
				int lp=i*2-1,rp=i*2;
				int lv=a[lp],rv=a[rp];
				if (lv||rv) {
					if ((lv<=n&&!rv)||(!lv&&rv<=n)) {
						ans=ans*rhs%mod;
						rhs--;
					} else if ((lv>n&&!rv)||(!lv&&rv>n)) {
						ans=ans*lhs%mod;
						lhs--;
					}
				} else {
					if (lhs&&rhs) {
						ans=ans*lhs%mod*rhs%mod*2%mod;
						lhs--;
						rhs--;
					} else if (lhs) {
						ans=ans*lhs%mod*(lhs-1)%mod;
						lhs-=2;
					} else if (rhs) {
						ans=ans*rhs%mod*(rhs-1)%mod;
						rhs-=2;
					}
				}
			}
			cout<< ans<< "\n";
		}
		return 0;
	}
}

signed main () {
	freopen ("wo.in","r",stdin);
	freopen ("wo.out","w",stdout);
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	return mci::main (); 
}
