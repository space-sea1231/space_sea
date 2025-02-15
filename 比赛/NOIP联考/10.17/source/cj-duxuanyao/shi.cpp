#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define db double
using namespace std;
const int N=4e5+5,INF=1e9;
int n,c,a[N];
string s;
vector<int>ans;
void cg(int x){
    if(a[x])a[x-1]=a[x+1]=0;
    else a[x-1]^=1,a[x+1]^=1;
}
void pt(){
    printf("%lld %lld\n",c,(int)ans.size());
    for(auto x:ans)printf("%lld ",x);
    if(ans.size())printf("\n");
}
void sv(){
    cin>>s;
    if(s.length()==4){
        if(s=="0001"){
            ans.push_back(2);
            pt();return;
        }if(s=="0010"){
            ans.push_back(2),ans.push_back(3);
            pt();return;
        }if(s=="0011"){
            ans.push_back(3),ans.push_back(2),ans.push_back(3);
            pt();return;
        }if(s=="0100"){
            ans.push_back(3),ans.push_back(2);
            pt();return;
        }if(s=="0101"){
            pt();return;
        }if(s=="0110"){
            ans.push_back(2),ans.push_back(3),ans.push_back(2);
            pt();return;
        }if(s=="0111"){
            pt();return;
        }if(s=="1000"){
            ans.push_back(3);
            pt();return;
        }if(s=="1001"){
            ans.push_back(2),ans.push_back(3),ans.push_back(2),ans.push_back(3);
            pt();return;
        }if(s=="1010"){
            pt();return;
        }if(s=="1011"){
            pt();return;
        }if(s=="1100"){
            ans.push_back(2),ans.push_back(3),ans.push_back(2);
            pt();return;
        }pt();return;
    }
    n=s.length(),s=' '+s,ans.clear(),c=0;
    for(int i=1;i<=n;i++)a[i]=s[i]-'0',c+=a[i];
    if(n==3){
        if(!c)ans.push_back(2);
        pt();return;
    }
    if(n<3||c>=n-1){pt();return;}
    for(int i=1;i+2<n;i++){
        if(a[i])continue;
        if(a[i+1])ans.push_back(i+2),cg(i+2);
        ans.push_back(i+1),cg(i+1);
    }
    if(a[n-2]){
        if(a[n-1]||a[n]){c=n-1,pt();return;}
        ans.push_back(n-2),ans.push_back(n-1);
        ans.push_back(n-2),c=n-1,pt();return;
    }
    else{
        if(a[n-1]){
            if(a[n]){c=n-1,pt();return;}
            ans.push_back(n-3),ans.push_back(n-2);
            ans.push_back(n-3),ans.push_back(n-1);
            ans.push_back(n-2),c=n-1,pt();return;
        }else{
            if(a[n]){
                ans.push_back(n-1),ans.push_back(n-2);
                ans.push_back(n-1),ans.push_back(n-2);
                c=n-1,pt();return;
            }else{
                ans.push_back(n-1),c=n-1,pt();
                return;
            }
        }
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    freopen("shi.in","r",stdin);
    freopen("shi.out","w",stdout);
    int T=1;cin>>T;while(T--)sv();
    return 0;
}