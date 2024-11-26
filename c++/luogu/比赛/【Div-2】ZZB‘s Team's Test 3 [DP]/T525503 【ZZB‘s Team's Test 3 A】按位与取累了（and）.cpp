#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e6+10;
const int bit=32;
int n;
bool cnt[N][bit], vis[N];
vector<int> q[bit];
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    int a, now;
    for (int i=1; i<=n; i++){
        cin >> a;
        for (int j=31; j>=0; j--){
            //1010 
            //1001 
            //1010 
            //1000
            now=(1LL<<j);
            // cerr << now << endl;
            if (a>=now){
                // printf("%lld %lld %lld\n", i, a, now);
                a-=now;
                cnt[i][j]=1;
                q[j].push_back(i);
            }
        }
    }
    int siz, sum=0;
    for (int i=31; i>=0; i--){
        if (q[i].size()>=2){
            now=i;
            break;
        }
    }
    // printf("Debug1: %lld\n", now);
    siz=q[now].size();
    for (int i=0; i<siz; i++){
        vis[q[now][i]]=1;
    }
    for (int i=now; i>=0; i--){
        if (q[i].size()>=2){
            sum+=(1<<i);
            // printf("%lld %lld\n", i, sum);
        }else{
            continue;
        }
        siz=q[i].size();
        for (int j=1; j<=n; j++){
            if (vis[j]==1&&cnt[j][now]==0){
                vis[j]=0;
                for (int k=i; k>=0; k--){
                    if (cnt[j][k]){
                        q[k].pop_back();
                    }
                }
            }
        }
    }
    printf("%lld", sum);

    return 0;
}