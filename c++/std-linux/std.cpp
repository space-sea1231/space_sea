#include <bits/stdc++.h>
using namespace std;
const int N=110;
const int M=15;
int n, m;
int cnt;
int sit[M<<1];
int dp[N][M<<1];
void Dfs(int x, int cur){
    if (cur>=n){
        sit[++cnt]=x;
        return ;
    }
    Dfs(x, cur+1);
    Dfs(x+(cur<<1), cur+3);
}
bool Check(int x, int y){
    
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m;
    Dfs(0, 0);
    for (int i=1; i<=cnt; i++){
        dp[1][i]=1;
    }
    for (int i=2; i<=n; i++){
        for (int u=1; u<=cnt; u++){
            for (int v=1; v<=cnt; v++){
                if (Check(sit[u], sit[v])){

                }
            }
        }
    }
    return 0;
}