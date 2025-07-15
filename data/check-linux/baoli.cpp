#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+5;
string s[N];
map<int,int> t;
int n,now[N];
stack<int> sta;
int get(string s){
    while(!sta.empty())sta.pop();
    int len=s.size();s=" "+s;
    int res=0;
    for(int i=1;i<=len;i++){
        if(s[i]=='('){
            sta.push(1);
        }else{
            if(!sta.empty())sta.pop();
            else res--;
        }
    }
    if(res<0&&!sta.empty())return 1e9;
    else if(res<0){
        return res;
    }else{
        return sta.size();
    }
}
signed main(){
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> s[i];
        int cnt=get(s[i]);
        t[cnt]++;
        now[i]=cnt;
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        if(now[i]<0)continue;
        ans+=t[-now[i]];
    }
    cout << ans;
    return 0;
}