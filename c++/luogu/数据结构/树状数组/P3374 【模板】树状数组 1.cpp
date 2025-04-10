#include <bits/stdc++.h>
using namespace std;
const int N=5e5+10;
int n, m;
struct Binary_Indexed_Tree{
    int num[N];
    int lowbit(int x){
        return x&-x;
    }
    void add(int x, int y){
        for (int i=x; i<=n; i+=lowbit(i)){
            num[i]+=y;
        }
    }
    int sum(int x){
        int ans=0;
        for (int i=x; i>=1; i-=lowbit(i)){
            ans+=num[i];
        }
        return ans;
    }
}tree;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m;
    for (int i=1; i<=n; i++){
        int x;
        cin >> x;
        tree.add(i, x);
    }
    for (int i=1; i<=m; i++){
        int opt;
        cin >> opt;
        if (opt==1){
            int x, y;
            cin >> x >> y;
            tree.add(x, y);
        }
        if (opt==2){
            int x, y;
            cin >> x >> y;
            printf("%d\n", tree.sum(y)-tree.sum(x-1));
        }
    }
    return 0;
}