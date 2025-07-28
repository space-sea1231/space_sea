#include <bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int nxt[N];
int n, opt, x, y;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	for (int i=1; i<=n; i++)
	{
		cin >> opt;
		if (opt==1)
		{
			cin >> x >> y;
			nxt[y]=nxt[x];//把y的后一个元素设为x原来的后一个元素
			nxt[x]=y;//把x的后一个元素设为y
		}
		if (opt==2)
		{
			cin >> x;
			printf("%d\n", nxt[x]);
		}
		if (opt==3)
		{
			cin >> x;
			nxt[x]=nxt[nxt[x]];//把x的后一个元素设为x原来后一个元素的后一个元素
		}
	}
	return 0;
}