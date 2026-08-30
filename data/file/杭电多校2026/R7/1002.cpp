#include<bits/stdc++.h>
using namespace std;
#define ms0(_array) memset(_array,0,sizeof _array)
#define endl '\n'
int Case=1;
string s;
bool is[4],is2[4];
void Main(){
    cin>>s;
    ms0(is);
    for(int i=0;i<s.size()-1;i++) is[2*(s[i]-'0')+s[i+1]-'0']=1;
    for(int len=2;len<=6;len++){
        for(int t=0;t<(1<<len);t++){
            int i=0;
            for(int j=0;j<len;j++){
                while(i<s.size()){
                    if(s[i]-'0'==((t>>j)&1)) goto suc;
                    else i++;
                }
                goto nxt;
                suc:;
                i++;
            }
            ms0(is2);
            for(int j=0;j<len-1;j++) is2[2*((t>>j)&1)+((t>>j+1)&1)]=1;
            for(int i=0;i<4;i++) if(is2[i]!=is[i]) goto nxt;
            goto perf;
            nxt:;
        }
        goto fail;
        perf:;
        return cout<<len<<endl,void();
        fail:;
    }
    assert(0);
    return;
}
signed main(){
    cin>>Case;
    while(Case--) Main();
    return 0;
}