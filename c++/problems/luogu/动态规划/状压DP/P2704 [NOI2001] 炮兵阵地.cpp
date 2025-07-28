#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int N=1e2+10;
const int M=10;
int n, m;
int cnt=1;
int vis[N];
int sit[1<<M], sat[1<<M];
int dp[N][1<<M][1<<M];
bool Check(int x){
    return x&(x<<2)||x&(x<<1)||x&(x>>1)||x&(x>>2);
}
int Lowbit(int x){
    return x&-x;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m;
    for (int i=1; i<=n; i++){
        for (int j=1; j<=m; j++){
            char c;
            cin >> c;
            vis[i]=(vis[i]<<1)+(c=='H'?1:0);
        }
    }
    for (int i=1; i<(1<<m); i++){
        if (Check(i)){
            continue;
        }
        sit[++cnt]=i;
        int tmp=i;
        while (tmp){
            sat[cnt]++;
            tmp-=Lowbit(tmp);
        }
    }
    for(int i=1; i<=cnt; i++){	//处理第一排
		if((sit[i]&vis[1])==0){	//不能与地形冲突
			dp[1][i][1]=sat[i];
		}	
	}
    for (int i=1; i<=cnt; i++){
        if (sit[i]&vis[2]){
            continue;
        }
        for (int j=1; j<=cnt; j++){
            if (sit[j]&vis[1]){
                continue;
            }
            if ((sit[i]&sit[j])==0){
                dp[2][i][j]=sat[i]+sat[j];
            }
        }
    }
    for (int i=3; i<=n; i++){
        for (int j=1; j<=cnt; j++){
            if (sit[j]&vis[i]){
                continue;
            }
            for (int k=1; k<=cnt; k++){
                if (sit[k]&vis[i-1]||sit[k]&sit[j]){
                    continue;
                }
                for (int l=1; l<=cnt; l++){
                    if (sit[l]&vis[i-2]||sit[l]&sit[k]){
                        continue;
                    }
                    if ((sit[j]&sit[k])==0&&(sit[j]&sit[l])==0){
                        dp[i][j][k]=max(dp[i][j][k], dp[i-1][k][l]+sat[j]);
                    }
                }
            }
        }
    }
    int ans=0;
    for (int i=1; i<=cnt; i++){
        if (sit[i]&vis[n]){
            continue;
        }
        for (int j=1; j<=cnt; j++){
            if (sit[j]&vis[n-1]){
                continue;
            }
            ans=max(ans, dp[n][i][j]);
        }
    }
    printf("%lld\n", ans);

    return 0;
}