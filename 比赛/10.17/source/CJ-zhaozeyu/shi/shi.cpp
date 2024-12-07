#include<bits/stdc++.h>
using namespace std;

int main(){
    freopen("shi.in","r",stdin);
    freopen("shi.out","w",stdout);
    int T;
    cin>>T;
    while(T--){
        string s;
        cin>>s;
        int k=s.size();
        s=" "+s;
        int sum=0;
        for(int i=1;i<=k;i++){
            sum+=(s[i]=='1');
        }
        if(k<=2){
            cout<<sum<<" "<<0<<"\n";
            continue;
        }
        if(!sum){
            if(sum%2==0){

            }
        }
    }
    return 0;
}