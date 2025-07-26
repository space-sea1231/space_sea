#include <bits/stdc++.h>
#define int long long
using namespace std;
int t,n,a[305];
int check()
{
    int sum=0,cnt=1;
    for(int i=2;i<=n;i++)
    {
        if(a[i]>a[i-1])cnt++;
        else
        {
            cnt=1;
            sum+=(cnt)*(cnt+1)/2;
        }
    }
    return sum+(cnt)*(cnt+1)/2;
}
signed main()
{
    freopen("wei.in","r",stdin);
    freopen("wei.out","w",stdout);
    cin>>t;
    while(t--)
    {
        cin>>n;
        for(int i=1;i<=n;i++)cin>>a[i];
        int maxn=0;
        maxn=max(maxn,check());
        for(int i=1;i<=n;i++)
        {
            for(int j=i+1;j<=n;j++)
            {
                swap(a[i],a[j]);
                maxn=max(maxn,check());
                swap(a[i],a[j]);
            }
        }
        cout<<maxn<<"\n";
    }
    return 0;
}