#include "testlib.h"
// #include "testlib_for_lemons.h"
#include<bits/stdc++.h>
using namespace std;
const int N=(1<<20)+100;
int T,n,m,K,tg1,tg2;
string s;
int main(int argc,char *argv[]){
    // registerLemonChecker(argc,argv);
    registerTestlibCmd(argc,argv);
    T=inf.readInt(),tg1=tg2=1;
    while(T--){
        s=inf.readToken();
        n=s.size();
        s='b'+s; // K=ans.readInt();
        // if(ouf.readInt(0,n)!=K)tg1=0;
        m=ouf.readInt(0,n*13);
        while(m--){
            int x=ouf.readInt(2,n-1);
            if(s[x]=='0'){
                s[x-1]^=1;
                s[x+1]^=1;
            }else{
                s[x-1]=s[x+1]='0';
            }
        }
        // cerr<<K<<" "<<count(s.begin(),s.end(),'1')<<endl;
        if(count(s.begin(),s.end(),'1')!=K){
            tg2=0;
            // assert(0);
        }
    }
    if(tg2)quitf(_ok,"weige is very satisfied!");
    if(tg1) assert(0),quitp(0.2, "weige is a bit satisfied.");
    assert(0);
}