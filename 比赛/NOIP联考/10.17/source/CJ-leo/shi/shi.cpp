#include<bits/stdc++.h>
using namespace std;
void file_init(){
#ifndef ONLINE_JUDGE
    freopen("shi.in","r",stdin);
    freopen("shi.out","w",stdout);
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
int n;
string s;
void read(){
    cin>>s;
    n=s.size();
    s=" "+s;
    return ;
}
vector<int>ans;
void update(int x){
    if(s[x]=='0'){
        if(s[x-1]=='0'){
            s[x-1]='1';
        }else{
            s[x-1]='0';
        }
        if(s[x+1]=='0'){
            s[x+1]='1';
        }else{
            s[x+1]='0';
        }
    }else{
        s[x-1]=s[x+1]='0';
    }
    return ;
}
void get_ans(){
    ans.clear();
    for(int i=1;i<n;i++){
        if(s[i-1]=='0'){
            if(s[i]=='0'){
                ans.push_back(i);
                update(i);
            }else if(i+1<n){
                ans.push_back(i+1);
                update(i+1);
                ans.push_back(i);
                update(i);
            }
        }
    }
    return ;
}
void put_ans(){
    cout<<"0 "<<ans.size()<<"\n";
    for(int num:ans){
        cout<<num<<" ";
    }
    cout<<"\n";
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
        put_ans();
    }
    return 0;
}