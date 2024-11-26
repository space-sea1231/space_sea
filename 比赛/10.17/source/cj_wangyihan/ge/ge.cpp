#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int mod=998442353;
int t;
struct point 
{
    int x,id;
}a[20];
int cmp(point x,point y)
{
    return x.x<y.x;
}
int s[20],b[20];
vector <int > p[20];
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch<='9'&&ch>='0')x=x*10+ch-'0',ch=getchar();
	return x*f;
}
signed main()
{
    freopen("ge.in","r",stdin);
    freopen("ge.out","w",stdout);
    t=read();
    while(t--)
    {
        int n=read(),tot=0,m=read();
        if(n==1)
        {
            int ans=0;
            for(int i=1;i<=m;i++)
                a[i].x=read(),a[i].id=i,b[i]=a[i].x;
            sort(a+1,a+m+1,cmp);
            for(int i=1;i<=m;i++)
            {
                cin>>s[i];
                if(s[i]==1)
                {
                    tot++;
                    int sum=b[i]-a[1].x+a[m].x-b[i];
                    ans=max(ans,sum);
                }
            }
            cout<<ans<<" "<<tot<<endl;
        }
        else cout<<"NIE"<<endl;
    }
}