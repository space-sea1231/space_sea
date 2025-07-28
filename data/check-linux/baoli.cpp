#include <bits/stdc++.h>
#define endl "\n"

using namespace std;

const int N=1e6+5;

int t,n;

int times[25]=
{1,1,1,1,1,1,1,2,2,2,3,10};

struct Node
{
	int sc,c[15],ans,est;
	char ch[15];
	int flag;
}a[N];

map<string,int> mp;

int tong[15];

int f(int x)
{
	int sum=0,res=0,big=0;
	for(int i=1;i<=10;i++) tong[i]=0;
	for(int i=1;i<=5;i++)
	{
		sum+=a[x].c[i];
		tong[a[x].c[i]]++;
		big=max(big,a[x].c[i]*100+('d'-a[x].ch[i]));
	}
	int old=big;
	for(int i=1;i<=10;i++)
	{
		if(tong[i]>=4)
		{
			a[x].est=i;
			return 11;
		}
	}
	for(int i=1;i<=5;i++) 
	for(int j=i+1;j<=5;j++)
	for(int k=j+1;k<=5;k++)
	{
		int tot=a[x].c[i]+a[x].c[j]+a[x].c[k];
		if(tot%10==0)
		{
			int cnt=sum-tot;
			cnt=(cnt-1)%10+1;
			if(cnt>res)
			{
				res=cnt,big=old;
				a[x].flag=0;
			}
		}
		if(a[x].c[i]==a[x].c[j]&&a[x].c[j]==a[x].c[k])
		{
			int cnt=sum-tot;
			cnt=(cnt-1)%10+1;
			if(cnt>=res)
			{
				res=cnt,big=a[x].c[i];
				a[x].flag=1;
			}
		}
	}
	a[x].est=big;
	return res;
}

string str[N];

string s[5],ca[15];

signed main()
{
	cin>>t>>t>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>str[i];
		mp[str[i]]=i;
	}
	while(t--)
	{
		for(int i=1;i<=3;i++)
		{
			cin>>s[i];
			int id=mp[s[i]];
			for(int j=1;j<=5;j++)
			{
				cin>>ca[j];
				a[id].ch[j]=ca[j][0];
				a[id].c[j]=(ca[j].size()==2?((ca[j][1]=='A')?1:(ca[j][1]-'0')):10);
			}
			a[id].flag=0;
			a[id].sc=f(id);
		}
		for(int i=1;i<=3;i++)
		{
			for(int j=i+1;j<=3;j++)
			{
				int u=mp[s[i]],U=times[a[u].sc]*((a[u].flag&&a[u].sc!=11)+1);
				int v=mp[s[j]],V=times[a[v].sc]*((a[v].flag&&a[v].sc!=11)+1);
				if(a[u].sc>a[v].sc)
				{
					a[u].ans+=10*U;
					a[v].ans-=10*U;
				}
				else if(a[u].sc<a[v].sc)
				{
					a[u].ans-=10*V;
					a[v].ans+=10*V;
				}
				else
				{
					int win=(((a[u].flag>a[v].flag)||(a[u].est>a[v].est&&a[u].flag==a[v].flag))?1:-1);
					a[u].ans+=win*10*(win==1?U:V);
					a[v].ans-=win*10*(win==1?U:V);
				}
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		cout<<str[i]<<' '<<a[i].ans<<endl;
	}

	#define Pyrf_uqcat return
	#define is 0
	#define Lovely ;
	
	Pyrf_uqcat is Lovely

}
