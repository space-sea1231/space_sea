#include <iostream>
#include <stdio.h>
#include <vector>
#define int long long
#define __Debug

using namespace std;
typedef long long ll;

const int N=1e3+10;

ll n, m;
ll sum[N][N];
ll a[16]={1,4,6,7,10,11,13,16,18,19,21,24,25,28,30,31};
ll b[16]={2,3,5,8,9,12,14,15,17,20,22,23,26,27,29,32};
vector<int> vec1, vec2;

ll Pow(ll a, ll b){
    ll sum=1;
    while (b>0){
        if (b&1==true){
            sum=sum*a;
        }
        a=a*a;
        b=b>>1;
    }
    return sum;
}
void Check(){
    ll suma=0, sumb=0;
    for (int i=0; i<=m; i++){
        for (int j=0; j<(1<<(n-1)); j++){
            suma+=sum[vec1[j]][i];
            sumb+=sum[vec2[j]][i];
        }
        if (suma!=sumb){
            return;
        }
    }
    printf("%d ", vec1.size());
    for (auto &idx:vec1){
        printf("%d ", idx);
    }
    printf("\n");
    printf("%d ", vec2.size());
    for (auto &idx:vec2){
        printf("%d ", idx);
    }
    printf("\n\n");
    return;
}
void Search(int dep){
    if (dep>(1<<n)){
        Check();
        return;
    }
    if (vec1.size()<(1<<(n-1))){
        vec1.push_back(dep);
        Search(dep+1);
        vec1.pop_back();
    }
    if (vec2.size()<(1<<(n-1))){
        vec2.push_back(dep);
        Search(dep+1);
        vec2.pop_back();
    }
    return;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i=1; i<=(1<<n); i++){
        for (int j=0; j<=m; j++){
            sum[i][j]=Pow(i, j);
        }
    }
    
    Search(17);

    return 0;
}
/*
3 2:
4 1 4 6 7 
4 2 3 5 8 

4 3:
8 1 4 6 7 10 11 13 16 
8 2 3 5 8 9 12 14 15 

5 4:
16 1 4 6 7 10 11 13 16 18 19 21 24 25 28 30 31 
16 2 3 5 8 9 12 14 15 17 20 22 23 26 27 29 32 
*/