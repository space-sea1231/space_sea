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

int n; char str[1000005]; vector<int>vec;
namespace bf{
    int pre[1<<5],op[1<<5],M;
    void dfs(int S,int fa,int o){
        if(~pre[S]) return; pre[S]=fa,op[S]=o;
        for(int i=1,T;i<n-1;dfs(T,S,++i)) T=S^((S>>i&1?S:M)&((1<<i-1)|(1<<i+1)));
    }
    void solve(){
        memset(pre,0xff,128),memset(op,0,128); int ans=-1,S=0,p=-1; M=(1<<n)-1;
        for(int i=0;i<n;i++) S|=(str[i+1]^48)<<i; dfs(S,0,0);
        for(int i=0,t;i<(1<<n);i++) if(~pre[i] && (t=__builtin_popcount(i))>ans) p=i,ans=t;
        for(;op[p];p=pre[p]) vec.push_back(op[p]);
        reverse(vec.begin(),vec.end()),printf("%d %zu\n",ans,vec.size());
        for(int i:vec) printf("%d ",i); puts("");
    }
}

void f(int p){
    if(str[p]=='1') str[p-1]=str[p+1]='0';
    else str[p-1]^=1,str[p+1]^=1; vec.push_back(p);
}
signed main(){
    freopen("shi.in","r",stdin);
    freopen("shi.out","w",stdout);
    int T=read();
    while(T--){
        scanf("%s",str+1),n=strlen(str+1),vec.clear();
        if(n<=5){bf::solve(); continue;}
        if(count(str+1,str+n+1,'0')==0){printf("%d 0\n",n); continue;}
        for(int i=1;i<n-1;i++) if(str[i]=='1') f(i+1); // (1)
        if(str[n-1]=='1') f(n-1),f(n-3),f(n-2),f(n-3); // (2)
        else if(str[n]=='1') f(n-2),f(n-1),f(n-2); // (3)
        for(int i=1;i<n-2;f(++i)) if(str[i+1]=='1') f(i+2); // (4)/(5)
        switch((str[n-1]^48)|2*(str[n]^48)){
            case 0: f(n-1); break; // (6)
            case 1: f(n-3),f(n-2),f(n-1),f(n-3),f(n-2); break; // (7)
            case 2: f(n-3),f(n-2),f(n-3); break; // (8)
            case 3: break; // (9)
        } printf("%d %zu\n",n-1,vec.size());
        for(int i:vec) printf("%d ",i); puts("");
    }
    return 0;
}

/*
(1)
... 0000100 ...
... 0000001 ... 1 [1同理]
(2)
... 000001?
... 0000010 1
... 0010110 2
... 0010100 3
... 0000000 4
(3)
... 0000001
... 0001011 1
... 0001010 2
... 0000000 3

(4)
... 1100000 ...
... 1110100 ... 1
(5)
... 1110100 ...
... 1110001 ... 1 [1同理]
... 1111011 ... 2

(6)
... 1111000
... 1111101 1
(7)
... 1111010
... 1101010 1
... 1100000 2
... 1100101 3
... 1110001 4
... 1111011 5
(8)
... 1111001
... 1101001 1
... 1100011 2
... 1110111 3
(9)
... 1111011
*/