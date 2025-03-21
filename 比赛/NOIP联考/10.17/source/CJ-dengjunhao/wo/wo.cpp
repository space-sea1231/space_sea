#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod=998244353;
int a[2119810];
int vis[2119810];
vector<int> g,ga;
int read(){
    int ch=getchar(),x=0,f=1;
    for(;!isdigit(ch);ch=getchar())f=(ch=='-'?-1:1);
    for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
    return x*f;
}
signed main(){
    freopen("wo.in","r",stdin);
    freopen("wo.out","w",stdout);
    int T;
    cin>>T;
    while(T--){
        int n=read();
        n*=2;
        for(int i=0;i<=n;i++){
            vis[i]=0;
        }
        ga.clear();
        g.clear();
        for(int i=1;i<=n;i++){
            a[i]=read();
            vis[a[i]]++;
        }
        for(int i=1;i<=n;i++){
            int nxt=(i%2==1?i+1:i-1);
            if(a[i]==0 && a[nxt]!=0){
                ga.push_back(a[nxt]);
            }
        }
        sort(ga.begin(),ga.end());
        for(int i=0;i<ga.size();i++){
            g.push_back(ga[i]);
        }
        for(int i=1;i<=n;i++){
            if(vis[i]==0){
                g.push_back(i);
            }
        }
        sort(g.begin(),g.end());
        if(g.size()==0){
            cout<<1<<'\n';
            continue;
        }
        int Len_1=0,Len_2=0;
        int Mid=g[(g.size()-1)/2];
        for(int i=1;i<=n;i++){
            if(vis[i]==0){
                if(i<=Mid){
                    Len_1++;
                }else{
                    Len_2++;
                }
            }
        }
        long long ans=1;
        for(int i=0;i<ga.size();i++){
            if(ga[i]>Mid){
                ans*=Len_1;
                Len_1--;
            }else{
                ans*=Len_2;
                Len_2--;
            }
            ans%=mod;
        }
        while(Len_1){
            ans*=2;
            ans%=mod;
            ans*=Len_1;
            ans%=mod;
            ans*=Len_2;
            ans%=mod;
            Len_1--;
            Len_2--;
        }
        cout<<ans<<'\n';
    }
    return 0;
}