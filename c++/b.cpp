#include <bits/stdc++.h>
using namespace std;
const int N=3e5+10;
int n, tot;
int a[N];
bool vis[N];
struct node{
    int x, id;
    bool operator < (const node &a){
        return x>a.x;
    }
}e[N];
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n;
    for (int i=1; i<=n; i++){
        cin >> a[i];
        e[i].x=a[i];
        e[i].id=i;
    }
    sort(e+1, e+n+1);
    int maxn=1, minn=n;
    while (tot<n){
        while (maxn<minn&&vis[e[maxn].id]){
            maxn++;
        }
        while (maxn<minn&&vis[e[minn].id]){
            minn--;
        }
        int l=min(e[maxn].id, e[minn].id);
        int r=max(e[maxn].id, e[minn].id);
        for (int i=l; i<=r; i++){
            
        }
    }
    return 0;
}