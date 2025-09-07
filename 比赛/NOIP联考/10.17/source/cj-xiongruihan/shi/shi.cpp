#include <bits/stdc++.h>
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-') f=-1;ch=getchar();}
	while(ch<='9'&&ch>='0') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return x*f;
}
void write(int x)
{
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
    return;
}
signed main()
{
	int t;
	cin>>t;
	while(t--)
	{
		string s;
		cin>>s;
		int sum=0;
		for(int i=0;i<s.size();i++)
		{
			sum+=s[i]-48;
		}
//		00
		if(sum==0)
		{
			if(s.size()==2)
			{
				cout<<1<<" "<<1<<endl<<1;
			}
			else 
			{
				int sum=s.size()/4*4/2;
				if(s.size()%4!=0)
				{
					if(s.size()%4!=1)
					{
						sum+=1;
					}
				}
				cout<<s.size()<<" "<<sum<<endl;
				for(int i=1;i<=s.size();i+=4) cout<<i+1<<" "<<i+2<<" ";
				if(s.size()%4==2)
				{
					cout<<s.size();	
				}
				if(s.size()%4==3)
				{
					cout<<s.size()-1;
				}
				cout<<endl;
			}
			continue;
		}	
	}
// 11110
    return 0;
}

