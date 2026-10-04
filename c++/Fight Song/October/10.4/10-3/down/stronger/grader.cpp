#include "stronger.h"
#include <iostream>
using namespace std;
namespace {
    int n,cnt,stc,len,pt;
    bool flg;
    char st[410],res[410];
    string s;

}
inline void fail() {
    cout<<"-1\n";
    exit(0);
}
bool query(string s) {
    ++cnt;
    if (s.size()!=n||!flg) fail();
    for (char c:s) if (c!='0'&&c!='1') fail();
    stc=0;
    pt=0;
    for (int i=1;i<=len;++i) if (res[i]=='x') st[++stc]=s[pt++]^48;
    else {
        --stc;
        st[stc]=st[stc]>st[stc+1];
    }
    return st[1];
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>s;
    for (char c:s) if (c=='x') res[++len]='x',++n;
    else if (c=='(') st[++stc]='(';
    else if (c==')') {
        while (st[stc]!='(') res[++len]=st[stc--];
        --stc;
    }
    else {
        while (stc&&st[stc]!='(') res[++len]=st[stc--];
        st[++stc]='>';
    }
    for (int i=stc;i;--i) res[++len]=st[i];
    flg=1;
    if (stronger(n)!=s) fail();
    cout<<cnt<<endl;
}