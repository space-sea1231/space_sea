#include<bits/stdc++.h>
using namespace std;
void file_init(){
#ifndef ONLINE_JUDGE
    freopen("wei.in","r",stdin);
    freopen("wei.out","w",stdout);
#endif
    return ;
}
void fast_read(){
#ifndef cin
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
#endif
    return ;
}
const int N=4e5+10;
int n;
int p[N];
void read(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>p[i];
    }
    return ;
}
#define ll long long
ll sum;
void init(){
    sum=0;
    int lst=1;
    for(int i=1;i<n;i++){
        if(p[i]>p[i+1]){
            sum+=(i-lst+2)*(i-lst+1)>>1;
            lst=i+1;
        }
    }
    sum+=(n-lst+2)*(n-lst+1)>>1;
    return ;
}
ll ans;
void get_ans(){
    init();
    ans=sum;
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            swap(p[i],p[j]);
            init();
            ans=max(ans,sum);
            swap(p[i],p[j]);
        }
    }
    return ;
}
int main(){
    file_init();
    fast_read();
    int t;
    cin>>t;
    while(t--){
        read();
        get_ans();
        cout<<(unsigned)ans<<"\n";
    }
    return 0;
}
/*
1 0 6 5 0 0
*/