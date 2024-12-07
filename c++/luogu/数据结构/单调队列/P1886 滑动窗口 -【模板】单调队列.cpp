#include <bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int n, m, l=1, r=1;
int a[N];
deque<int> q;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	for (int i=1; i<=n; i++)
	{
		cin >> a[i];
	}
	for (int i=1; i<=n; i++)
	{
		while (!q.empty()&&a[q.back()]>a[i])
			q.pop_back();
		q.push_back(i);
		while (!q.empty()&&m+q.front()<i+1&&i>=m)
			q.pop_front();
		if (i>=m)
			printf("%d ", a[q.front()]);
	}
	while (!q.empty())
		q.pop_back();
	printf("\n");
	for (int i=1; i<=n; i++)
	{
		while (!q.empty()&&a[q.back()]<a[i])
			q.pop_back();
		q.push_back(i);
		while (!q.empty()&&m+q.front()<i+1&&i>=m)
			q.pop_front();
		if (i>=m)
			printf("%d ", a[q.front()]);
	}
	return 0;
}