#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define debug false 
#define pts10 true

#if debug
bool M_st;
void Dub();
#endif

const int N=2e6+5,mod=998244353;
int n,wz[N],ans,maxi=-1e9,a[N],tot,num[N];
bool vis[N];
//vector<vector<int> >kn;

void update()
{
	for(int i=1;i<=tot;i++)
		a[wz[i]]=num[i];
	int now=0;
	for(int i=1;i<=2*n;i+=2)
		now+=abs(a[i]-a[i+1]);
	for(int i=1;i<=tot;i++)
		a[wz[i]]=0;
#if debug
	if(n==2&&num[1]==1&&num[2]==3&&num[3]==2&&num[4]==4)
		cerr<<now<<"\n";
#endif
	if(now>maxi)
	{
		maxi=now,ans=1;//,kn.clear();
//		vector<int>V;
//		V.clear();
//		for(int i=1;i<=tot;i++)
//			V.push_back(num[i]);
//		kn.push_back(V);
	}
	else if(now==maxi)
	{
		ans=(ans+1)%mod;
//		vector<int>V;
//		V.clear();
//		for(int i=1;i<=tot;i++)
//			V.push_back(num[i]);
//		kn.push_back(V);
	}
	return ;
}

void dfs(int cur)
{
//	cout<<cur<<" "<<tot<<"\n";
	if(cur==tot+1)
	{
		update();
		return ;
	}
	for(int i=1;i<=2*n;i++)
		if(vis[i]==false)
		{
			vis[i]=true;
			num[cur]=i;
			dfs(cur+1);
			vis[i]=false;
		}
	return ;
}

void Work()
{
	int sz1=n,sz2=n;
	ans=1;
	for(int i=1;i<=2*n;i++)
	{
		cin>>a[i];
		if(a[i]>0&&a[i]<=n)
			sz1--;
		if(a[i]>n)
			sz2--;
	}
	for(int i=1;i<=2*n;i+=2)
	{
#if debug
		cerr<<ans<<" "<<sz1<<" "<<sz2<<" "<<(a[i]>0)<<" "<<(a[i+1]>0)<<"\n";
#endif
		if(a[i]==0&&a[i+1]==0)
		{
			if(sz1>=1&&sz2>=1)
				ans=(ans*sz1*sz2*2)%mod,sz1--,sz2--;
			else if(sz1>=2)
				ans=(ans*sz1*(sz1-1)*2)%mod,sz1-=2;
			else if(sz2>=2)
				ans=(ans*sz2*(sz2-1)*2)%mod,sz2-=2;
		}
		else if(a[i]==0||a[i+1]==0)
		{
			int pos=i;
			if(a[i]==0)
				pos++;
			if(a[pos]<=n)
			{
				if(sz2>=1)
					ans=(ans*sz2)%mod,sz2--;
				else
					ans=(ans*sz1)%mod,sz1--;
			}
			else
			{
				if(sz1>=1)
					ans=(ans*sz1)%mod,sz1--;
				else
					ans=(ans*sz2)%mod,sz2--;
			}
		}
	}
	cout<<ans<<"\n";
	return ;
}

signed main()
{
	freopen("wo.in","r",stdin);
	freopen("wo.out","w",stdout);
	int T,tt,lstmx=0;
	cin>>T;
	tt=T;
	while(T--)
	{
		cin>>n;
		lstmx=max(lstmx,n);
#if debug
		cerr<<lstmx<<" "<<n<<" "<<tt<<"\n";
#endif
		if(lstmx<=4&&lstmx*tt<=100&&pts10)
		{
			tot=0;
			for(int i=1;i<=2*n;i++)
				vis[i]=false;
			for(int i=1;i<=2*n;i++)
			{
				cin>>a[i];
				if(a[i]==0)
					wz[++tot]=i;
				else
					vis[a[i]]=true;
			}
//			kn.clear();
			ans=0,maxi=-1e18;
			dfs(1);
			int tmp=ans;
			cout/*<<maxi<<" "*/<<ans<<"\n";
//			for(auto Vv:kn)
//			{
//				for(auto v:Vv)
//					cout<<v<<" ";
//				cout<<"\n";
//			}
//			if(tmp!=ans)
//			{
//				cerr<<"Wrong!!!\n";
//				return 114514;
//			}
			continue;
		}
		Work();
	}
#if debug
	Dub();
#endif
	return 0;
}

#if debug
bool M_ed;
void Dub()
{
//	cerr<<"\n\n========================================================\n";
//	cerr<<"time: "<<clock()/1000.0<<" , "<<abs(&M_ed-&M_st)/1024.0/1024.0<<" MB\n";
	return ; 
}
#endif
