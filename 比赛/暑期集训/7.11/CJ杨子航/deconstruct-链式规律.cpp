#include <iostream>
#include <stdio.h>
#define __Debug

using namespace std;
typedef long long ll;

const int N=1e2+10;

int n=5;
int num[N], siz[N], cnt[N];
bool vis[N], flag[N];

void Dfs2(){
    for (int i=1; i<=n; i++){
        siz[i]=n-i;
        flag[i]=false;
    }
    printf("num: ");
    for (int i=1; i<n; i++){
        printf("%d ", num[i]);
    }
    printf("\n");
    printf("Debug1: ");
    for (int i=1; i<n; i++){
        cnt[siz[num[i]]]++;
        printf("%d ", siz[num[i]]);
        int tmp=siz[num[i]];
        for (int j=num[i]; j>=1&&flag[j]==false; j--){
            siz[j]-=tmp;
        }
        flag[num[i]]=true;
    }
    printf("\n");
}
void Dfs1(int dep){
    if (dep==n){
        Dfs2();
        return;
    }
    for (int i=1; i<n; i++){
        if (vis[i]==false){
            vis[i]=true;
            num[dep]=i;
            Dfs1(dep+1);
            vis[i]=false;
        }
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Dfs1(1);
    int sum=0;
    for (int i=1; i<n; i++){
        printf("%d:%d\n", i, cnt[i]);
        sum+=i*cnt[i];
    }
    printf("sum=%d\n", sum);
    return 0;
}