#include <bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int t, n, l_1, l_2, r_1, r_2, st, ed;
int sum_1[N], sum_2[N], a[N], b[N];
char c[N];
bool flag;
bool dfs(int now, int l_1, int r_2)
{
	if (l_1==2)
		c[1]='L';
	else
		c[1]='R';
	r_1=now, l_2=now, st=1, ed=n;
	for (int i=1; i<n/2; i++)
	{
		if (b[a[l_1]+n/2]==r_1-1)
		{
			l_1++, r_1--;
			c[++st]='L';
			c[--ed]='L';
		}
		else if (b[a[l_1]+n/2]==l_2+1)
		{
			l_1++, l_2++;
			c[++st]='L';
			c[--ed]='R';
		}
		else if (b[a[r_2]]==r_1-1)
		{
			r_1--, r_2--;
			c[++st]='R';
			c[--ed]='L';
		}
		else if (b[a[r_2]]==l_2+1)
		{
			l_2++, r_2--;
			c[++st]='R';
			c[--ed]='R';
		}
		else
		{
			return 0;
		}
	}
	c[n]='L';
	for (int i=1; i<=n; i++)
		printf("%c", c[i]);
	printf("\n");
	return 1;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> t;
	while (t--)
	{
		cin >> n, n*=2;
		for (int i=1; i<=n; i++)
			b[i]=0;
		for (int i=1; i<=n; i++){
			cin >> a[i];
			if (b[a[i]])
				b[a[i]+n/2]=i;
			else
				b[a[i]]=i;
		}
		if(dfs(b[a[1]+n/2], 2, n)){
			continue;
		}
		if(dfs(b[a[n]], 1, n-1)){
			continue;
		}
		printf("-1\n");
	}
	return 0;
}