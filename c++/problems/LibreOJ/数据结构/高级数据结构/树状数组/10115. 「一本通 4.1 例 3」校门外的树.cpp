#include <bits/stdc++.h>
using namespace std;
const int N=5e4+10;
int n, m;
struct Binary_Indexed_Tree{
    int num_1[N], num_2[N];
    int lowbit(int x){
        return x&-x;
    }
    void add_1(int x, int y){
        for (int i=x; i<=n; i+=lowbit(i)){
            num_1[i]+=y;
        }
    }
    void add_2(int x, int y){
        for (int i=x; i<=n; i+=lowbit(i)){
            num_2[i]+=y;
        }
    }
    int sum_1(int x){
        int ans=0;
        for (int i=x; i>=1; i-=lowbit(i)){
            ans+=num_1[i];
        }
        return ans;
    }
    int sum_2(int x){
        int ans=0;
        for (int i=x; i>=1; i-=lowbit(i)){
            ans+=num_2[i];
        }
        return ans;
    }
}tree;
int main(){
    ios::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m;
    for (int i=1; i<=m; i++){
        int opt;
        cin >> opt;
        if (opt==1){
            int x, y;
            cin >> x >> y; 
            tree.add_1(x, 1);
            tree.add_2(y, 1);
        }
        if (opt==2){
            int x, y;
            cin >> x >> y;
            printf("%d\n", tree.sum_1(y)-tree.sum_2(x-1));
        }
    }

    return 0;
}