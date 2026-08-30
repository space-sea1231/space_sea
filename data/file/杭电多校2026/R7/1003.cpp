#include <bits/stdc++.h>
using namespace std;
char s[55];
int mp[300];
array<int,16> emp;
inline bool single_turn(array<int,16> &a)
{
	int sum=accumulate(a.begin(),a.end(),0);
	int mx=*max_element(a.begin(),a.end());
	int cnt1=count(a.begin(),a.end(),1);
	if(sum==4 && a[14]==2 && a[15]==2) return true;
	if(sum==mx) return true;
	if(sum==5 && mx==3 && cnt1==0) return true;
	if(a[13]+a[14]+a[15]==0 && mx<=3)
	{
		bool fl=true;
		int L=0,R=0;
		for(int i=1;i<=15;i++)
		{
			if(!a[i]) continue;
			if(a[i]!=mx){fl=false;break;}
			if(!L) L=i;
			R=i;
		}
		if(fl && mx*(R-L+1)==sum) return true;
	}
	if(sum%5==0)
	{
		int len=sum/5;
		for(int l=1,r=len;r<=12;l++,r++)
		{
			bool fl=true;
			for(int i=1;i<=15;i++)
			{
				int num=a[i]-(l<=i&&i<=r?3:0);
				if(num<0 || (num&1)){fl=false;break;}
			}
			if(fl) return true;
		}
	}
	return false;
}
pair<int,int> maxbomb;
bool dfs1(int p,array<int,16> a)
{
	if(p==15) return single_turn(a);
	if(p==14)
	{
		if(dfs1(p+1,a)) return true;
		if(a[14]==2 && a[15]==2)
		{
			a[14]=a[15]=0;
			return dfs1(p+1,a);
		}
		return false;
	}
	if(dfs1(p+1,a)) return true;
	for(int i=a[p];i>=1;i--)
	{
		if(make_pair(i,p)<maxbomb) break;
		a[p]-=i;
		if(dfs1(p+1,a)) return true;
		a[p]+=i;
	}
	return false;
}
bool solve()
{
	scanf("%s",s+1);
	assert(strlen(s+1)==33);
	array<int,16> a=emp;
	for(int i=1;i<=33;i++) assert(mp[s[i]]),a[mp[s[i]]]++;
	if(a[14]+a[15]==0) return single_turn(a);
	maxbomb={0,0};
	for(int i=1;i<=13;i++) maxbomb=max(maxbomb,make_pair(8-a[i],i));
	return dfs1(1,a);
}
int main()
{
	mp['3']=1;mp['4']=2;mp['5']=3;mp['6']=4;mp['7']=5;
	mp['8']=6;mp['9']=7;mp['T']=8;mp['J']=9;mp['Q']=10;
	mp['K']=11;mp['A']=12;mp['2']=13;mp['w']=14;mp['W']=15;
	int t;
	cin>>t;
	while(t--) printf(solve()?"Yes\n":"No\n");
}
