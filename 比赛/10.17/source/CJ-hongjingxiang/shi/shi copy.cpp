#include <bits/stdc++.h>
#define ll long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
using namespace std;

inline static int read(){
    int sum=0,neg=0,ch=getchar();
    while(!isdigit(ch)) neg|=(ch=='-'),ch=getchar();
    while(isdigit(ch)) sum=sum*10+(ch^48),ch=getchar();
    return neg?-sum:sum;
}

constexpr int op[2][2]={{1,0},{0,0}};
set<vector<int>>Set;
void dfs(const vector<int>&a){
    if(!Set.insert(a).second) return;
    for(int i=1;i<a.size()-1;i++){
        vector<int>b=a;
        b[i-1]=op[b[i-1]][b[i]];
        b[i+1]=op[b[i+1]][b[i]];
        dfs(b);
    }
}
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    dfs({1,0,0,0});
    for(auto i:Set){for(int j:i) printf("%d ",j); puts(""); exit(0);}
    return 0;
}
/*

... 0000001
... 0001011 1
... 0001010 2
... 0000000 3

... 0000100 ...
... 0000001 ... 1 [1同理]

... 1100000 ...
... 1110100 ... 1

... 1110100 ...
... 1110001 ... 1 [1同理]
... 1111011 ... 2


... 1111100
... 1101000 1
... 1101101 2
... 1100101 3
... 1110001 4
... 1111011 5


*/