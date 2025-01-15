#include<bits/stdc++.h>
using namespace std;
using ui=unsigned int;
const int N=4e5+3;
int a[N];
int n;
void solve(){
    cin>>n;
    for(int i=1;i<=n;++i)cin>>a[i];
    ui ans=0;
    for(int i=1;i<=n;++i)
        for(int j=i+1;j<=n;++j){
            swap(a[i],a[j]);ui res=0;
            for(int l=1,r=1;l<=n;++l){
                if(l==r)++r;
                while(r<=n&&a[r]>a[r-1])++r;
                res+=r-l;
            }
            swap(a[i],a[j]);ans=max(ans,res);
        }
    printf("%u\n",ans);
}
int main(){
    int u,v,w,x,y,z;
    freopen("wei.in","r",stdin);
    freopen("wei.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int T;for(cin>>T;T--;)solve();
    return 0;
}