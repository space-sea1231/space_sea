#include <bits/stdc++.h>
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
int main(){
    ios::sync_with_stdio(0);
    cin >> n >> m;
    int opt;
    while (cin >> opt){
        if (opt==1){
            int sx, sy, fx, fy, z;
            cin >> sx >> sy >> fx >> fy >> z;
            tree.add(sx, sy, z);
            tree.add(fx+1, sy, -z);
            tree.add(sx, fy+1, -z);
            tree.add(fx+1, fy+1, z);
        }
        if (opt==2){
            int x, y;
            cin >> x >> y;
            printf("%d\n", tree.query(x, y));
        }
    }
    return 0;
}