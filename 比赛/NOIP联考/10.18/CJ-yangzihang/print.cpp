#include <bits/stdc++.h>
using namespace std;
const int N=1e3+10;
int n, m, cnt;
char c[N][N];
string s;
vector<int> q;
void fen(){
    int i;
    for (i=1; i*i<m; i++){
        if (m%i==0){
            cnt+=2;
            q.push_back(i);
            q.push_back(m/i);
        }
    }
    i++;
    if (i*i==m){
        cnt++;
        q.push_back(i);
    }
}
signed main(){
    freopen("print.in", "r", stdin);
    freopen("print.out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
    cin >> n >> m;
    char yes;
    bool flag=1;
    for (int i=1; i<=n; i++){
        for (int j=1; j<=m; j++){
            cin >> c[i][j];
            if (i==1&&j==1){
                yes=c[i][j];
            }else if(c[i][j]!=yes){
                flag=0;
            }
        }
    }
    if (n==1&&flag){
        fen();
        printf("%d\n", cnt);
        sort(q.begin(), q.end());
        for (int i=0; i<q.size(); i++){
            printf("%d ", q[i]);
        }
        return 0;
    }
    for (int len=0; len<min(n, m); l++){//枚举长度
        for(int j=1; j<=n; j++){//枚举当前行
            for (int l=1; l+len<=m; l++){//枚举字符串A左端点
                s="";
                for (int i=l; i<=l+len; l++){//取出
                    s+=c[j][i];
                }
                check(s);
            }
        } 
        
    }
    return 0;
}