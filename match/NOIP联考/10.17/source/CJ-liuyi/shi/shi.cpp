#include<bits/stdc++.h>
using namespace std;
#define rint register int

int T,n,ans[13000005],tot;
string s;
inline void print(rint res){
    cout<<res<<" "<<tot<<"\n";
    for(rint i=1;i<=tot;i++)cout<<ans[i]<<" ";
    cout<<"\n";
}
int main(){
    freopen("shi.in","r",stdin);
    freopen("shi.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>T;
    while(T--){
        cin>>s,n=s.size(),s=" "+s,tot=0;
        if(n==1){
            cout<<(s[0]=='1'?1:0)<<"\n";
            continue;
        }
        if(n==2){
            if(s==" 11")cout<<"2 0\n";
            else if(s==" 00")cout<<"0 0\n";
            else cout<<"1 0\n";
            continue;
        }
        for(rint i=1;i<=n-2;i++){
            if(s[i]=='1'){
                s[i]='0',ans[++tot]=i+1;
                if(i+2>n)continue;
                if(s[i+1]=='0'&&s[i+2]=='0')s[i+2]='1';
                else s[i+2]='0';
            }
        }
        if(s[n-1]=='1'){
            for(rint i=1;i+4<n;i+=2){
                s[i]=s[i+1]='1';
                ans[++tot]=i+1,ans[++tot]=i+3,ans[++tot]=i+2,ans[++tot]=i+4;
            }
            if(n==3)print(1);
            else if(n==4){
                if(s[n]=='1')ans[++tot]=2,print(3);
                else ans[++tot]=2,ans[++tot]=3,print(3);
            }else{
                if(s[n]=='1')ans[++tot]=n-3,print(n-1);
                else ans[++tot]=n-3,ans[++tot]=n-1,ans[++tot]=n-2,ans[++tot]=n-1,print(n-1);
            }
        }else{
            if(s[n]=='0'){
                for(rint i=1;i+4<n;i+=2){
                    s[i]=s[i+1]='1';
                    ans[++tot]=i+1,ans[++tot]=i+3,ans[++tot]=i+2,ans[++tot]=i+4;
                }
                if(n==3)ans[++tot]=n-1;
                else if(n==4)ans[++tot]=n-3,ans[++tot]=n,ans[++tot]=n-1;
                else ans[++tot]=n-3,ans[++tot]=n-1,ans[++tot]=n-2;
                print(n-1);
            }else{
                if(n==3)print(1);
                else print(n-1);
            }
        }
    }
    return 0;
}