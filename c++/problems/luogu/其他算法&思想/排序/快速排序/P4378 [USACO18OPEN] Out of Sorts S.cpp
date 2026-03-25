#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n;
struct node{
    int id;
    int w;
    bool operator<(const node &a){
        if (w==a.w){
            return id<a.id;
        }
        return w<a.w;
    }
}e[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n;
    for (int i=1; i<=n; i++){
        cin >> e[i].w;
        e[i].id=i;
    }
    sort(e+1, e+n+1);
    int maxn=0;
    for (int i=1; i<=n; i++){
        maxn=max(maxn, e[i].id-i+1);
    }
    printf("%d\n", maxn);

    return 0;
}