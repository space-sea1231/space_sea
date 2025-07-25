#include <iostream>
#include <stdio.h>
#include <cmath>
#include <stack>
// #define __Debug

using namespace std;
typedef long long ll;

const int N=5e4+10;

int n, m;
int siz, num;
int id[N], sum[N];
bool vis[N];
stack<int> house;

bool Check(int l, int r){
    for (int i=l; i<=r; i++){
        if (vis[i]==true){
            return false;
        }
    }
    return true;
}
int Search(int cur){//3 5 6
    int l=id[cur], r=id[cur];
    if (Check((id[cur]-1)*siz+1, cur)){
        l=max(1, l-1);
        while (l>1&&sum[l]==0){
            l--;
        }
    }
    if (Check(cur, id[cur]*siz)){
        r=min(num, r+1);
        while (r<num&&sum[r]==0){
            r++;
        }
    }
    #ifdef __Debug
        printf("Debug4: l=%d r=%d\n", l, r);
    #endif
    int L, R;
    for (int i=(l==id[cur]?cur:min(l*siz, n)); i>=1; i--){
        L=i;
        if (vis[i]==true){
            L=i+1;
            break;
        }
    }
    for (int i=(r==id[cur]?cur:(r-1)*siz+1); i<=n; i++){
        R=i;
        if (vis[i]==true){
            R=i-1;
            break;
        }
    }
    return max(R-L+1, 0);
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    siz=sqrt(n);
    for (int i=1; i<=n; i+=siz){
        num++;
        for (int j=i; j<=min(n, i+siz-1); j++){
            id[j]=num;
            #ifdef __Debug
                printf("Debug1: id[%d]=%d\n", j, id[j]);
            #endif
        }
    }
    for (int i=1; i<=m; i++){
        char opt;
        cin >> opt;
        if (opt=='D'){
            int x;
            cin >> x;
            if (vis[x]==false){
                vis[x]=true;
                sum[id[x]]++;
                house.push(x);
            }
        }
        if (opt=='R'){
            int x=house.top();
            house.pop();
            vis[x]=false;
            sum[id[x]]--;
        }
        if (opt=='Q'){
            int x;
            cin >> x;
            #ifdef __Debug
                for (int j=1; j<=num; j++){
                    printf("Debug2: sum[%d]=%d\n", j, sum[j]);
                }
            #endif
            // #ifdef __Debug
            //     for (int i=1; i<=n; i++){
            //         printf("Debug1: vis[%d]=%d\n", i, vis[i]);
            //     }
            // #endif
            printf("%d\n", Search(x));
        }
    }
    return 0;
}