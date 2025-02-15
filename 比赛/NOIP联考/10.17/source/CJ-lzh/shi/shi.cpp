#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int T,n;
char c[N];
bool a[N];
vector<int> rans[7][65];
int dans[7][65];
bool check()
{
    for(int i=1;i<=n;i++)
        if(!a[i]) return false;
    return true;
}
int ans[N*10],anscnt,anss;
void print()
{
    cout<<anss<<' '<<anscnt<<'\n';
    for(int i=1;i<=anscnt;i++) cout<<ans[i]<<' '; cout<<'\n';
}
void calc(int l,int r)
{
    int p=0,len=r-l+1;
    for(int i=l;i<=r;i++) p=p*2+a[i];
    for(int x:rans[len][p]) ans[++anscnt]=x+l-1; anss=dans[len][p];
}
void add(int x)
{
    ans[++anscnt]=x;
    a[x-1]=!(a[x]|a[x-1]);
    a[x+1]=!(a[x]|a[x+1]);
}
void solve()
{
    cin>>c+1; n=strlen(c+1); anscnt=0;
    for(int i=1;i<=n;i++) a[i]=c[i]-'0';
    // if(check()) return cout<<n<<' '<<0<<'\n'<<'\n',void();
    // if(n<=2) return cout<<0<<' '<<0<<'\n'<<'\n',void();
    // if(n==3)
    // {
    //     if(!a[2]) anss=(a[1]==a[3]?1:2),ans[++anscnt]=2;
    //     else anss=(a[1]==a[3]?2:1);
    //     return print();
    // }
    // if(n==4)
    // {
    //     if(!a[1]) ans[++anscnt]=1+1,a[1]=!(a[1]|a[1+1]),a[1+2]=!(a[1+2]|a[1+1]);
    //     if(!a[n]) ans[++anscnt]=n-1,a[n]=!(a[n]|a[n-1]),a[n-2]=!(a[n-2]|a[n-1]);
    //     if(!a[1]) ans[++anscnt]=1+1,a[1]=!(a[1]|a[1+1]),a[1+2]=!(a[1+2]|a[1+1]);
    //     if(!a[n]) ans[++anscnt]=n-1,a[n]=!(a[n]|a[n-1]),a[n-2]=!(a[n-2]|a[n-1]);
    //     anss=0;
    //     for(int i=1;i<=n;i++) anss+=a[i];
    //     return print();
    // }
    if(n<=6)
    {
        calc(1,n);
        return print();
    }
    int l=1,r=n;
    while(r-l+1>4)
    {
        if(!a[r])
        {
            if(a[r-1]) add(r-2),add(r-1),r--;
            else add(r-1),r--;
        } else r--;
        if(!a[l])
        {
            if(a[l+1]) add(l+2),add(l+1),l++;
            else add(l+1),l++;
        } else l++;
    }
    calc(l-1,r+1); print();
    // if(n==5)
    // {
    //     // if(!a[1]&&!a[2]&&a[3]&&!a[4]&&!a[5]) 
    // }
    // if(n<=8) return calc(1,n);
}
vector<int> nans;
int pans=0;
void dfs(int dep,int x,int i,int j)
{
    int ans=__builtin_popcount(x);
    if(ans>pans||ans==pans&&nans.size()<rans[i][j].size()) pans=ans,rans[i][j]=nans;
    if(dep==0) return ;
    for(int p=1;p<i-1;p++)
    {
        nans.push_back(i-p);
        int px=x;
        if((x>>p&1))
        {
            if(x>>(p-1)&1) x^=1<<(p-1);
            if(x>>(p+1)&1) x^=1<<(p+1);
        }
        else
        {
            x^=1<<(p-1);
            x^=1<<(p+1);
        }
        dfs(dep-1,x,i,j);
        x=px;
        nans.pop_back();
    }
}
void init(int i,int j)
{
    nans.clear(); pans=0;
    dfs(7,j,i,j); dans[i][j]=pans;
}
int main()
{
    freopen("shi.in","r",stdin);
    freopen("shi.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    for(int i=1;i<=6;i++)
    for(int j=0;j<1<<i;j++)
        init(i,j);
    cin>>T; while(T--) solve();
}