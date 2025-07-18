#include <iostream>
#include <stdio.h>
#include <vector>
#define __Debug

using namespace std;
typedef long long ll;

const int N=1e5+10;

int n, m;
bool vis[N];
vector<int> vec1, vec2;

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    vis[1]=0;
    for (int i=3; i<=n; i++){
        for (int j=(1<<(i-3))+1; j<=(1<<(i-2)); j++){
            vis[j]=vis[j-(1<<(i-3))]^1;
        }
    }
    // for (int i=1; i<=(1<<(n-2)); i++){
    //     printf("%d ", vis[i]);
    // }
    // return 0;
    int cnt=0;
    for (int i=1; i<=(1<<(n-2)); i++){
        if (vis[i]==1){
            vec1.push_back(++cnt);
            vec2.push_back(++cnt);
            vec2.push_back(++cnt);
            vec1.push_back(++cnt);
        }
        else{
            vec2.push_back(++cnt);
            vec1.push_back(++cnt);
            vec1.push_back(++cnt);
            vec2.push_back(++cnt);
        }
    }
    printf("1\n");
    printf("%d ", vec1.size());
    for (auto &idx:vec1){
        printf("%d ", idx);
    }
    printf("\n");
    printf("%d ", vec2.size());
    for (auto &idx:vec2){
        printf("%d ", idx);
    }
    return 0;
}