#include <bits/stdc++.h>
using namespace std;
char s[205]; 
int a[205];
int to[10];
int nxt[205], num[205], len[205];

int main()
{
	freopen("mex.in", "r", stdin);
	freopen("mex.out", "w", stdout);
	int n, i, j, p;
	bool b = 1;
	scanf("%d", &n);
	scanf("%s", s + 1);
	for(i = 1; i <= n; i++)
	{
		a[i] = s[i] - '0';
		if(!a[i])
			b = 0;
	}
	if(b)
	{
		printf("0\n");
		return 0;
	}
	for(i = n; i >= 1; i--)
	{
		nxt[i] = to[0];
		num[i] = 0;
		len[i] = len[to[0]] + 1;
		for(j = 1; j < 10; j++)
			if(len[to[j]] < len[nxt[i]])
			{
				nxt[i] = to[j];
				num[i] = j;
				len[i] = len[to[j]] + 1;
			}
		to[a[i]] = i;
	}
	p = 1;
	for(j = 2; j < 10; j++)
		if(len[to[j]] < len[to[p]])
			p = j;
	printf("%d", p);
	p = to[p];
	while(p)
	{
		printf("%d", num[p]);
		p = nxt[p];
	}
	printf("\n");
	return 0;
}
