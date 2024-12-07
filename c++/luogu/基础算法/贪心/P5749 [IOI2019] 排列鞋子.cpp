#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
int n, ans;
int tree[N<<1], a[N];
bool vis[N];
vector<int> q[N<<1];
int lowbit(int x){
    return x&-x;
}
void add(int x, int w){
    while (x<=(n<<1)){
        tree[x]+=w;
        x+=lowbit(x);
    }
}
int sum(int x){
    int ans=0;
    while (x){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n;
    for (int i=1; i<=(n<<1); i++){
        cin >> a[i];
        q[a[i]+n].push_back(i);
        add(i, 1);
    }
    for (int i=(n<<1); i>=1; i--){
        if (vis[i]){
            continue;
        }
        int r=q[n-a[i]].back();
        q[a[i]+n].pop_back();
        q[n-a[i]].pop_back();
        add(i, -1);
        add(r, -1);
        ans+=sum(i)-sum(r-1);
        vis[i]=1;
        vis[r]=1;
        if (a[i]<0){
            ans++;
        }
    }
    printf("%lld", ans);

    return 0;
}