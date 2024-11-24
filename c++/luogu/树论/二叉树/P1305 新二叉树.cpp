#include <bits/stdc++.h>
using namespace std;
const int N=130;
int n, cnt;
char l[N], r[N], start;
void init()
{
	for (int i=0; i<N; i++) l[i]='*', r[i]='*';
}
void serch(char dep)
{
	if (dep=='*') return ;
	printf("%c", dep);
	serch(l[dep]);
	serch(r[dep]);
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n, init();
	char u, v, mid;
	for (int i=1; i<=n; i++)
	{
		cin >> mid >> u >> v;
		l[mid]=u, r[mid]=v;
		if (i==1) start=mid;
	}
	serch(start);

	return 0;
}