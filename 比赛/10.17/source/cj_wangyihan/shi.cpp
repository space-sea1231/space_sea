#include<bits/stdc++.h>
#define int long long 
const int maxx=25;
using namespace std;
int t,len,maxn,flag;
char a[1000005];
int dis[1000005],ans[1000005],pre[1000005],fac[1000005],las[1000005];
struct point 
{
    int x,dis;
    bool operator <(const point &i)const{
        return dis>i.dis;
    }
};
void bfs()
{
    memset(dis,127,sizeof(dis));
    int now=0;
    for(int i=1;i<=len;i++)
        now=now*2+(a[i]-'0');
    priority_queue <point > p;
    dis[now]=0;
    pre[now]=-1;
    p.push((point){now,0});
    while(!p.empty())
    {
        int u=p.top().x,d=p.top().dis;
        p.pop();
        int tot=0;
        for(int i=0;i<len;i++)
            if((u>>i)&1) tot++;
        if(tot>maxn)
        {
            maxn=tot;
            flag=u;
        }
        for(int i=2;i<len;i++)
        {
            int now=(u>>(len-i))&1,now1=(u>>(len-i+1))&1,now2=(u>>(len-i-1))&1;
            int v=u-(1<<(len-i+1))*now1-(1<<(len-i-1))*now2;
            now1=(!now)&&(!now1),now2=(!now)&&(!now2);
            v=v+(1<<(len-i+1))*now1+(1<<(len-i-1))*now2;
            if(d+1<dis[v])
            {
                dis[v]=d+1;
                pre[v]=i;
                ans[v]=u;
                p.push((point){v,dis[v]});
            }
        }
    }
}
signed main()
{
    freopen("shi.in","r",stdin);
    freopen("shi.out","w",stdout);
    cin>>t;
    fac[0]=1;
    for(int i=1;i<=maxx;i++)
        fac[i]=fac[i-1]*2;
    while(t--)
    {
		flag=0;
        int fuck=0,sum=0;
        cin>>(a+1);
        len=strlen(a+1);
        for(int i=1;i<=len;i++)
        {
            sum+=a[i]-'0';
            if(!(a[i]-'0')) flag=1;
            if(a[i]-'0') fuck=1;
        }
        if(sum==1)
        {
            int flag,maxx=0,las;
            for(int i=1;i<=len;i++)
                if(a[i]-'0'==1) flag=i;
            for(int i=flag;i<=len;i+=2)
            {
                int now=(i-1)/3*2+(len-i)/3*2+1;
                if(now>maxx) maxx=now,las=i;
            }
            for(int i=flag;i>=1;i-=2)
            {
                int now=(i-1)/3*2+(len-i)/3*2+1;
                if(now>maxx) maxx=now,las=i;
            }
            printf("%lld %lld\n",maxx,(flag-las)/2+(las-1)/3+(len-las)/3);
            if(las<flag)
                for(int i=flag;i!=las;i-=2)
                    printf("%lld ",i-1);
            else for(int i=flag;i!=las;i+=2)
                printf("%lld ",i+1);
            for(int i=2;i<las-1;i+=3)
                printf("%lld ",i);
            for(int i=las+2;i<=len;i+=3)
                printf("%lld ",i);
            cout<<endl;
            continue;
        }
        if(!fuck)
        {
            int ans=len/3*2;
            printf("%lld %lld\n",ans,len/3);
            for(int i=2;i<len;i+=3)
                printf("%lld ",i);
            printf("\n");
            continue;
        }
        if(!flag)
        {
            printf("%lld %lld\n",len,0);
            continue;
        }
        else 
        {
        	int num=0;
            maxn=0;
            bfs();
            printf("%lld %lld\n",maxn,dis[flag]);
            while(pre[flag]!=-1)
            {
                las[++num]=pre[flag];
                flag=ans[flag];
            }
            for(int i=num;i>=1;i--)
                printf("%lld ",las[i]);
            printf("\n");
        }
    }
}