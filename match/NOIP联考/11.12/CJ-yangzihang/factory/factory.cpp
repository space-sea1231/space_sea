#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int T, n, m;
int c[N], l[N], r[N], v[N], t[N];
int main(){
	freopen("factory.in", "r", stdin);
	freopen("factory.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie();
	cin >> T;
	while (T--){
		cin >> n >> m;
		for (int i=1; i<=n; i++){
			cin >> c[i];
		}
		for (int i=1; i<=m; i++){
			cin >> l[i] >> r[i] >> v[i] >> t[i];
		}
		if (m==1){
			if (t[1]==1){
				for (int i=1; i<=n; i++){
					int ll=min(l[1], i);
					int rr=max(r[1], i);
					int sum=0;
					for (int j=ll; j<=rr; j++){
						sum+=c[j];
					}
					printf("%d ", min(sum, v[1]));
				}
			}else{
				int sum=0;
				for (int i=l[1]; i<=r[1]; i++){
					sum+=c[i];
				}
				sum=min(sum, v[1]);
				for (int i=1; i<=n; i++){
					printf("%d ", sum);
				}
			}
			printf("\n");
		}
	}

	return 0;
}