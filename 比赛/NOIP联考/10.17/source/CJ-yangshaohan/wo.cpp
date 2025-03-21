#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int a[100005],n,ans,cnt1,cnt2,dt1,dt2;
int A(int mm,int tem)
{
    if(tem==0||mm==0)
        return 1;
    int sum=1;
    while(tem--)
    {
        sum*=mm%mod;
        mm--;
    }
    return sum%mod;
}
int ksm(int k)
{
    if(k==1)
        return 2;
    if(k==0)
        return 1;
    int sum=1;
    if(k%2==1)
        sum*=2;
    int p=ksm(k/2)%mod;
    sum*=p*p%mod;
    return sum;
}
signed main()
{
    freopen("wo.in","r",stdin);
    freopen("wo.out","w",stdout);
    int t;
    cin>>t;
    // cout<<ksm(t+3);
    while(t--)
    {
        cin>>n;
        cnt1=n,cnt2=n;
        dt1=0,dt2=0;
        // n=n*2;
        for(int i=1;i<=n*2;i++) 
            cin>>a[i];
        for(int i=1;i<=n;i++)
        {
            // if(a[i*2-1]!=0&&a[i*2]!=0)
            // {
            //     if((a[i*2-1]<=n&&a[i*2]>n)||(a[i*2-1]>n&&a[i*2]<=n))//没司马且符合当前最优状态
            //     {
            //         continue;
            //     }
            //     else//司马懿了两次
            //     {
            //         if(a[i*2]<=n)
            //             cnt1-=2;
            //         else
            //             cnt2-=2;
            //     }
            // }
            int x=a[i*2-1],y=a[i*2];
            if(x==0&&y==0)
                continue;
            if(x==0)
            {
                if(y<=n)
                cnt1--,dt1++;
                else
                cnt2--,dt2++;
                continue;
            }
            if(y==0)
            {
                if(x<=n)
                cnt1--,dt1++;
                else
                cnt2--,dt2++;
                continue;
            }
            if(x<=n)
            cnt1--;
            else
            cnt2--;
            if(y<=n)
            cnt1--;
            else
            cnt2--;
        }//肯定是把左边的挪一块到右边所结合，不然就司马了
        int ans=1;
        // cout<<cnt1<<' '<<cnt2<<' '<<dt1<<' '<<dt2<<"\n";
        ans*=A(cnt2,dt1)%mod;
        cnt2-=dt1;
        // cout<<ans<<"\n";
        ans*=A(cnt1,dt2)%mod;
        // cout<<ans<<"\n";
        cnt1-=dt2;
        if(cnt1>cnt2)
            swap(cnt1,cnt2);
        if(cnt1==0&&cnt2!=0)
            ans*=A(cnt2/2,cnt2/2)%mod*A(cnt2/2,cnt2/2)%mod*ksm(cnt2/2)%mod;
        else if(cnt1!=0&&cnt2==0)
            ans*=A(cnt1/2,cnt1/2)%mod*A(cnt1/2,cnt1/2)%mod*ksm(cnt1/2)%mod;
        else if(cnt1!=0&&cnt2!=0)
        {
            // cout<<ans;
            ans*=A(cnt1,cnt1)%mod*A(cnt1,cnt1)%mod*ksm(cnt1)%mod;
            // cout<<ans;
            ans*=A((cnt2-cnt1)/2,(cnt2-cnt1)/2)%mod*A((cnt2-cnt1)/2,(cnt2-cnt1)/2)%mod;
        }
        cout<<ans%mod<<"\n";
    }
    return 0;
}
