#include<iostream>
#include<string>

using namespace std;

int n;
string s;

int mxdep;
int mxsta[1000],mxtail,ans;
int sta[1000],tail;
static inline void dfs(int dep){
    int ret=0;
    for(int i=1;i<=n;++i)
        ret+=s[i]=='1';
    if(ret>ans||(ret==ans&&tail<mxtail)){
        ans=ret;
        for(int i=1;i<=tail;++i)
            mxsta[i]=sta[i];
        mxtail=tail;
    }
    if(dep==mxdep)
        return;
    for(int i=2;i<n;++i){
        sta[++tail]=i;
        string o=s;
        if(s[i]=='0'){
            s[i-1]^=1;
            s[i+1]^=1;
        }else{
            s[i-1]='0';
            s[i+1]='0';
        }
        dfs(dep+1);
        s=o;
        --tail;
    }
}

static inline void solve(){
    cin>>s;
    n=(int)s.size();
    s=' '+s;
    mxdep=13*n;
    mxtail=0;
    ans=0;
    dfs(1);
    cout<<ans<<' '<<mxtail<<endl;
    for(int i=1;i<=mxtail;++i)
        cout<<mxsta[i]<<' ';
    cout<<endl;
}

signed main(){
    freopen("shi.in","r",stdin);
    freopen("shi.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin>>T;
    while(T--)
        solve();
    return 0;
}