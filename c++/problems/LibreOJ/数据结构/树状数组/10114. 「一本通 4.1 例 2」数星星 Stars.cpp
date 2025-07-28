#include <bits/stdc++.h>
using namespace std;
const int N=4e4+10;
int n;
int cnt[N];
struct Binary_Indexed_Tree{
    int num[N];
    int lowbit(int x){
        return x&-x;
    }
    void add(int x, int y){
        for (int i=x; i<N; i+=lowbit(i)){
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
    cin >> n;
    for (int i=1; i<=n; i++){
        int x, y;
        cin >> x >> y;
        cnt[tree.sum(++x)]++;
        tree.add(x, 1);
    }
    for (int i=0; i<n; i++){
        printf("%d\n", cnt[i]);
    }
    
    return 0;
}