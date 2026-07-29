#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

const int Mod=1e9+7;
const int N=50;

int m, l;
int cnt, tot;
int a[N];
int tmp[N];

bool check(){
    for (int i=1; i<=l; i++){
        if (tmp[i]>a[i]){
            return 0;
        }
        if (tmp[i]<a[i]){
            return 1;
        }
    }
    return 0;
}
void search(int dep, int sum){//3 3
    // printf("%d %d\n", dep, sum);
    if (dep==0&&sum==0&&check()){
        cnt++;
        // for (int i=1; i<=l; i++){
        //     printf("%d ", tmp[i]);
        // }
        // printf("\n");
        return ;
    }
    for (int i=max(0, sum-(dep-1)*(m-1)); i<min(sum+1, m); i++){
        tmp[l-dep+1]=i;
        search(dep-1, sum-i);
    }
}
signed main(){
    freopen("digit.in", "r", stdin);
    freopen("digit.out", "w", stdout);
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> m >> l;
    for (int i=1; i<=l; i++){
        cin >> a[i];
        tot+=a[i];
    }
    search(l, tot);
    printf("%d\n", cnt);

    return 0;
}