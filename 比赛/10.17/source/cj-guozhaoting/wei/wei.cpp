#include<bits/stdc++.h>
using namespace std;
#define int unsigned 

int pf(int x)
{
	return x*x;
}

const int N=4e5+5;
int n,L[N],a[N],R[N],pos[N],tot,ip[N],ans,maxi;

signed main()
{
	freopen("wei.in","r",stdin);
	freopen("wei.out","w",stdout);
	int T;
	cin>>T;
	while(T--)
	{
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			ip[a[i]]=i;
		}
		for(int i=n;i>=1;i--)
		{
			if(a[i]>a[i+1])
				L[tot++]=i+1,R[tot]=i;
			pos[i]=tot;
		}
		L[tot]=1,L[0]=ans=0;
		for(int i=1;i<=tot;i++)
			ans+=(R[tot]-L[tot]+1)*(R[tot]-L[tot]+1);
		maxi=ans;
		cout<<maxi<<"\n";
	}
//	for(int i=tot;i>1;i--)
//	{
//		int lenN=(R[i]-L[i]+1),lenL=(R[i-1]-L[i-1]+1),now=ans;
//		ans+=(lenN+lenL)*(lenN+lenL)-lenN*lenN-lenL*lenL;
//		if(lenN==1||a[R[i]-1]<a[L[i-1]])
//		{
//			int tmpL=L[i-1];
//			L[i-1]=L[i];
//			int tmpR=R[i];
//			R[i]=R[i-1];
//			for(int j=a[R[i]-1]+1;j<a[L[i-1]];j++)
//			{
//				int p=ip[j],kp=pos[ip[j]];
//				if(a[p-1]<a[R[i]]&&a[R[i]]<a[p+1])
//				{
//					if(L[kp]==R[kp])
//					{
//						ans--;
//						ans-=pf(R[kp+1]-L[kp+1]+1);
//						ans-=pf(R[kp-1]-L[kp-1]+1);
//						ans+=pf((R[kp+1]-L[kp+1]+1)+(R[kp-1]-L[kp-1]+1)+1);
//					}
//					
//				}
//			}
//		}
//	}
//	cout<<maxi;
	return 0;
}
