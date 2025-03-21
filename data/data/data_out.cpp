#include <bits/stdc++.h>
using namespace std;
const int TEST=50;
const string id="U526216";
const string problem="理智的采药";
const string file="/home/space_sea/space_sea/data/data/"+id+"/";
int Random(int l, int r){
    return rand()%(r-l+1)+l;//生成随机数
}

#define int long long
const int N=1e4+10;
const int M=1e7+10;
int n, m, cnt;
int dp[M], val[M], vis[M];
void init(){
    memset(dp, 0, sizeof(dp));
    memset(val, 0, sizeof(val));
    memset(vis, 0, sizeof(vis));
    cnt=0;
}
void date_out(){
	init();
	cin >> m >> n;
    for (int i=1; i<=n; i++){
        int v, w, c;
        cin >> v >> w >> c;
        for (int j=30; j>=0; j--){
            if (c>=(1<<j)){
                c-=((1<<j));
                vis[++cnt]=v*(1<<j);
                val[cnt]=w*(1<<j);
            }
        }
    }
    for (int i=1; i<=cnt; i++){
        for (int j=m; j>=vis[i]; j--){
            dp[j]=max(dp[j], dp[j-vis[i]]+val[i]);
        }
    }
    printf("%lld\n", dp[m]);
}
signed main(){
    srand(time(NULL));//随机种子
    for (int task=1; task<=TEST; task++){
        string file_in="";
        file_in+=file+problem+"_";
        file_in+=to_string(task)+".in";
        freopen(file_in.c_str(), "r", stdin);

        string file_out="";
        file_out+=file+problem+"_";
        file_out+=to_string(task)+".out";
        freopen(file_out.c_str(), "w", stdout);
        date_out();
    }
	fclose(stdin);
	fclose(stdout);
    system("rm data_out");

    return 0;
}