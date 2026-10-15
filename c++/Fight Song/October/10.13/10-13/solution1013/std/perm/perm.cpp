#include "perm.h"
using namespace std;
vector<int> q,invq,known,r;
vector<int> perm(int c,int n) {
    for(int i = 0;i < n;i++)q.push_back(i), invq.push_back(i);
	known.push_back(0);
	for(int i = 1;i < n;i++)
	{
		if(!query(q, 0, i))
		{
			swap(invq[0], invq[i]);
			for(int j = 0;j < n;j++)q[invq[j]] = j;
			known.insert(known.end(), i);
			continue;
		}
		vector <int> cur = q, curinv = invq;
		int l = 1, r = known.size() - 1, pos = 0;
		while(l <= r)
		{
			int mid = (l + r) / 2;
			swap(invq[0], invq[known[mid]]);
			for(int j = 0;j < n;j++)q[invq[j]] = j;
			if(!query(q, 0, i))pos = mid, l = mid + 1;
			else r = mid - 1;
			q = cur, invq = curinv;
		}
		known.insert(known.begin() + pos + 1, i);
	}
	r.resize(n + 2);
	for(int i = 0;i < n;i++)r[known[(i + n - 1) % n]] = known[i];
	for(int i = 0;i < n;i++)q[i] = invq[r[i]];
	return q;
}