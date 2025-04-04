#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
const int T=N-9, F=-N+9, U=0;
int c, t, n, m;
bool vis[300005];

int fa[N];
int Find(int x) {
	if (x==T||x==F){
        return x;
    }
    if (vis[n-x]||x==U){
        return U;
    }
    if (vis[x+n]){
        return T;
    }
    if (x<0){
		if (x==-fa[-x]){
            return x;
        }
        vis[x+n]=1;
        int tmp=Find(-fa[-x]);
        vis[x+n]=0;
        return tmp;
	}
    if (x>0){
		if (x==fa[x]){
            return x;
        }
        vis[x+n]=1;
        fa[x]=Find(fa[x]);
        vis[x+n]=0;
        return fa[x];
	}
    return 0;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
	cin >> c >> t;
	while (t--){
		cin >> n >> m;
		for(int i=1; i<=n; i++){
            fa[i]=i;
        }
		for(int i=1; i<=m; i++){
            int x, y;
            char c;
			cin >> c;
			if (c=='T'){
				cin >> x;
				fa[x]=T;
			}else if(c=='F'){
				cin >> x;
				fa[x]=F;
			}else if(c=='U'){
				cin >> x;
				fa[x]=U;
			}else{
				cin >> x >> y;
				if (c=='+'){
                    fa[x]=fa[y];
                }else{
                    fa[x]=-fa[y];
                }
			}
		}
		int ans=0;
		for (int i=1; i<=n; i++){
			if (Find(i)==U){
                ans++;
            }
		}
		printf("%lld\n", ans);
	}

	return 0;
}