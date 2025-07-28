#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[400010];
#define low(i) i&(-i)
int n;
unordered_map<int,int>tree;
void change(int x,int y){
    for(int i=x;i>=1;i-=low(i)){
        tree[i]+=y;
    }
}
int ask(int x){
    int sum=0;
    for(int i=x;i<=n;i+=low(i)){
        sum+=tree[i];
    }
    return sum;
}

signed main(){
    freopen("wei.in","r",stdin);
    freopen("wei.out","w",stdout);
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>a[i];
        }
        int sum=0;
        for(int i=1;i<=n;i++){
            sum+=ask(a[i]);
            change(a[i],1);
        }
        int minn=sum;
        for(int i=1;i<n;i++){
            for(int j=i+1;j<=n;j++){
                swap(a[i],a[j]);
                tree.clear();
                int ss=0;
                for(int k=i;k<=j;k++){
                    ss+=ask(a[k]);
                    change(a[k],1);
                }
                minn=min(minn,ss);
                swap(a[i],a[j]);
            }
        }
        cout<<n*(n+1)/2-minn<<"\n";
    }
    return 0;
}