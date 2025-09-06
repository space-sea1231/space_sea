#include <bits/stdc++.h>
#define int long long
using namespace std;
const int M=998244353;
const int N=(2e6)+5;
int n,t,jc[N],fpow[N],a[N];
struct node
{
    int x,y;
}c[N];
bool cmp(node a,node b)
{
    return max(a.x,a.y)<max(b.x,b.y);
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    freopen("wo.in","r",stdin);
    freopen("wo.out","w",stdout);
    jc[0]=fpow[0]=1;
    for(int i=1;i<=2e6;i++)
    {
        jc[i]=jc[i-1]*i%M;
        fpow[i]=fpow[i-1]*2%M;
    }
    cin>>t;
    while(t--)
    {
        cin>>n;
        int cnt1=0,cnt2=0,l=n,cnt=0,cur=0;
        for(int i=1;i<=2*n;i++)
        {
            cin>>a[i];
            if(i%2==0)
            {
                c[++cur].y=a[i];
                c[cur].x=a[i-1];
            }
        }
        sort(c+1,c+cur+1,cmp);
        for(int i=1;i<=cur;i++)
        {
            if(!c[i].x)continue;
            if(!c[i].y)continue;
            if(max(c[i].x,c[i].y)<=l)l++;
            else break;
        }
        for(int i=1;i<=cur;i++)
        {
            if(max(c[i].x,c[i].y)<=l&&c[i].x&&c[i].y)n--;
            else if(min(c[i].x,c[i].y)>=l&&c[i].x&&c[i].y)n--;
            else
            {
                if(c[i].x)
                {
                    if(c[i].x<=l)cnt1++;
                    else cnt2++;
                }
                if(c[i].y)
                {
                    if(c[i].y<=l)cnt1++;
                    else cnt2++;
                }
                if(c[i].x==0&&c[i].y==0)cnt++;
            }
        }
        cout<<(jc[n-cnt1]*jc[n-cnt2]%M)*fpow[cnt]%M<<"\n";
    }
    return 0;
}
//I AK wby,wby AK cxm so I AK cxm
//jyq AK IOI!taijule!!%%%sto jyq orz