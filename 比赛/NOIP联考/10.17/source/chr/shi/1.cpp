#include<bits/stdc++.h>
using namespace std;
const int N=5;
int f[1<<N];
pair<int,int> pre[1<<N];
int n;
vector<int> op;
string s;
void change(int i)
{
    if(!(s[i]=='1'&&s[i-1]=='0')) s[i-1]=s[i-1]=='1'?'0':'1';
    if(!(s[i]=='1'&&s[i+1]=='0')) s[i+1]=s[i+1]=='1'?'0':'1';
}
void print(int x,int l)
{
    if(pre[x].first==-1) return ;
    print(pre[x].first,l);
    op.push_back(pre[x].second+l);
    change(op.back());
}
void dp(int x,int n,int l)
{
    int p=x;
    memset(f,-1,sizeof(f));
    memset(pre,-1,sizeof(pre));
    f[x]=0,pre[x]=make_pair(-1,0);
    queue<int> q;
    q.push(x);
    while(q.size())
    {
        x=q.front();
        q.pop();
        for(int i=1;i<n-1;i++)
        {
            int y=x;
            if(!((y>>i-1&1^1)&&(y>>i&1))) y^=1<<i-1;
            if(!((y>>i+1&1^1)&&(y>>i&1))) y^=1<<i+1;
            if(f[y]!=-1) continue;
            f[y]=f[x]+1;
            pre[y]=make_pair(x,i);
            q.push(y);
        }
    }
    for(int i=0;i<(1<<n);i++)
        if(f[i]!=-1&&__builtin_popcount(i)>__builtin_popcount(p))
            p=i;
    // for(int i=0;i<n;i++) cerr<<(p>>i&1);
    // cerr<<'\n';
    print(p,l);
}
void work(int l,int r)
{
    if(r-l+1<=5) 
    {
        int x=0;
        for(int i=0;i<=r-l;i++) x|=(s[l+i]=='1')<<i;
        // cerr<<s<<'\n';
        dp(x,r-l+1,l);
        return ;
    }
    if(s[l]=='1') ;
    else if(s[l+1]=='0')
    {
        op.push_back(l+1);
        change(l+1);
    }
    else
    {
        op.push_back(l+2);
        change(l+2);
        op.push_back(l+1);
        change(l+1);
    }
    // cerr<<l+1<<' '<<r<<' '<<s<<endl;
    work(l+1,r);
}
void run()
{
    cin>>s;
    n=s.size();
    s=' '+s;
    int cnt=0;
    for(int i=1;i<=n;i++) cnt+=s[i]=='0';
    if(!cnt)
    {
        cout<<n<<" 0"<<'\n';
        cout<<'\n';
        return ;
    }
    op.clear();
    work(1,n);
    int ans=0;
    for(int i=1;i<=n;i++) ans+=s[i]=='1';
    cout<<ans<<' ';
    cout<<op.size()<<'\n';
    for(int i:op) cout<<i<<' ';
    cout<<'\n';
    // cerr<<s<<'\n';
} 
signed main()
{
    // freopen("1.in","r",stdin);
    // freopen("1.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
    int t;
    cin>>t;
    while(t--) run();
	return 0;
}
