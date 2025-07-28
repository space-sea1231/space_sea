#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
typedef pair<int,int> PII;
string s;
void cah(int x){
    s[x]='1',s[x+1]='0',s[x+2]='1';
}
void cha(int x){
    s[x]='1',s[x+1]='0',s[x+2]='0';
}
signed main(){
    freopen("shi.in","r",stdin);
    freopen("shi.out","w",stdout);
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin>>T;
    while(T--){
        cin>>s;
        // if(s=="")
        n=s.size();s=" "+s;
        bool Fl=1;
        for(auto x:s) if(x=='1'){Fl=0;break;}
        if(Fl){
            cout<<((s.size()-1)/2)*2<<" "<<0<<"\n";
            int cnt=((s.size()-1)/2)*2;
            continue;
        }
        bool flag=0;
        for(auto x:s) if(x=='0'){flag=1;break;}
        if(!flag){
            cout<<n<<" "<<0<<"\n";
            continue;
        }
        vector<PII> res;
        for(int i=1;i<=n-3;i++){
            string tmp;tmp+=s[i];
            tmp+=s[i+1],tmp+=s[i+2];
            if(tmp=="000") res.push_back({i+1,1}),cah(i);
            else if(tmp=="010") res.push_back({i+1,2}),cah(i);
            else if(tmp=="100") ;
            else if(tmp=="001") res.push_back({i+1,1}),cha(i);
            else if(tmp=="110") res.push_back({i+1,3}),cah(i);
            else if(tmp=="011") res.push_back({i+1,3}),cah(i);
            else if(tmp=="111") res.push_back({i+1,3}),cah(i);
            // cout<<s<<endl;
        }
        string tmp;tmp+=s[n-2];
        tmp+=s[n-1];tmp+=s[n];
        if(tmp=="100"||tmp=="001") cout<<n-2<<" ";
        else{
            cout<<n-1<<" ";
            int i=n-2;
            if(tmp=="000") res.push_back({i+1,1}),cah(i);
            else if(tmp=="010") res.push_back({i+1,2}),cah(i);
            else if(tmp=="100") ;
            else if(tmp=="001") res.push_back({i+1,1}),cha(i);
            else if(tmp=="110") res.push_back({i+1,3}),cah(i);
            else if(tmp=="011") res.push_back({i+1,3}),cah(i);
            // else if(tmp=="111") res.push_back({i+1,3}),cah(i);
        }
        int sum=0;
        for(auto x:res) sum+=x.second;
        cout<<sum<<"\n";
        for(auto x:res){
            for(int i=0;i<x.second;i++) cout<<x.first<<" ";
        }
        cout<<"\n";
    }
}