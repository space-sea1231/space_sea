#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=(1<<12)+10;
int n, m;
struct Binary_Indexed_Tree{
    int num[N][N];
    int lowbit(int x){
        return x&-x;
    }
    void add(int x, int y, int z){
        for (int i=x; i<=n; i+=lowbit(i)){
            for (int j=y; j<=m; j+=lowbit(j)){
                num[i][j]+=z;
            }
        }
    }
    int query(int x, int y){
        int sum=0;
        for (int i=x; i>=1; i-=lowbit(i)){
            for (int j=y; j>=1; j-=lowbit(j)){
                sum+=num[i][j];
            }
        }
        return sum;
    }
}tree;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m;
    int opt;
    while (cin >> opt){
        if (opt==1){
            int x, y, z;
            cin >> x >> y >> z;
            tree.add(x, y, z);
        }
        if (opt==2){
            int sx, sy, fx, fy, sum=0;
            cin >> sx >> sy >> fx >> fy;
            sum+=tree.query(fx, fy)+tree.query(sx-1, sy-1);
            sum-=tree.query(sx-1, fy)+tree.query(fx, sy-1);
            printf("%lld\n", sum);
        }
    }

    return 0;
}