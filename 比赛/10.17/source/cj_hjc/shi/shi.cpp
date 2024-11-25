#include<bits/stdc++.h>
using namespace std;
const int N=1000005;
int T,n,ct,ans[N*10],a[N];
string s;
int main()
{
    freopen("shi.in","r",stdin);
    freopen("shi.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>T;
    while(T--)
    {
        cin>>s;ct=0;int n=s.size();
        for(int i=1;i<=n;++i)
        {
            a[i]=(s[i-1]=='1');
        }
        if(n>4)
        {
            int cc=0;
            for(int i=1;i<=n;++i)
            {
                cc+=a[i];
            }
            if(cc==n)
            {
                cout<<n<<" "<<0<<"\n";
                continue;
            }
            for(int i=2;i<n;++i)
            {
                if(a[i-1])ans[++ct]=i,a[i-1]=((!a[i])&(!a[i-1])),a[i+1]=((!a[i])&(!a[i+1]));
            }
            if(a[n-1]&&a[n])ans[++ct]=n-1,a[n-1-1]=((!a[n-1])&(!a[n-1-1])),a[n-1+1]=((!a[n-1])&(!a[n-1+1]));
            if(a[n-1])
            {
                ans[++ct]=n-2,ans[++ct]=n-1;
                ans[++ct]=n-2,ans[++ct]=n-1;
            }
            if(a[n])
            {
                ans[++ct]=n-1,ans[++ct]=n-1;
            }
            ans[++ct]=2;
            for(int i=2;i<=n-3;++i)
            {
                ans[++ct]=i+2,ans[++ct]=i+1;
                if(i!=n-3)ans[++ct]=i+2;
            }
            cout<<n-1<<" "<<ct<<"\n";
            for(int i=1;i<=ct;++i)cout<<ans[i]<<" ";
            cout<<"\n";
        }
        else
        {
            if(n==3)
            {
                int cc=0;
                for(int i=1;i<=n;++i)
                {
                    cc+=a[i];
                }
                if(cc=0)cc=2,ans[++ct]=2;
                cout<<cc<<" "<<ct<<"\n";
                for(int i=1;i<=ct;++i)cout<<ans[i]<<" ";
                cout<<"\n";
            }
            if(n==4)
            {
                int cc=0;
                for(int i=1;i<=n;++i)
                {
                    cc+=a[i];
                }
                if(cc==1)
                {
                    cc=3;
                    if(a[1])ans[++ct]=3;
                    else if(a[2])ans[++ct]=3,ans[++ct]=2;
                    else if(a[3])ans[++ct]=2,ans[++ct]=2;
                    else if(a[4])ans[++ct]=2;
                }
                cout<<cc<<" "<<ct<<"\n";
                for(int i=1;i<=ct;++i)cout<<ans[i]<<" ";
                cout<<"\n";
            }
        }
    }
    return 0;
}