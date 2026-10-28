## 常见形式

$dp_{i,j}=\min (dp_{i,j},dp_{i,k}+dp_{k+1,j}+w_{i,j})$。

注意：一般只能优化取$\min$的情形。

## 四边形不等式

若$l \le l' \le r' \le r$且$w_{l,r'}+w_{l',r} \le w_{l',r'}+w_{l,r}$，称函数$w$满足四边形不等式。（相交不大于包含）

## 区间包含单调性

若$l \le l' \le r' \le r$且$w_{l',r'} \le w_{l,r}$，称函数$w$具有区间包含单调性。

## 一些定理

1.  若$w$满足四边形不等式和区间包含单调性，那么$dp$就满足四边形不等式。
2.  设$pos_{i,j}$表示$dp_{i,j}$的最优决策点，当$dp$满足四边形不等式时，那么$pos_{i,j}$满足：$pos_{l,r-1} \le pos_{l,r} \le pos_{l+1,r}$。

以上证明可以使用导数+找极值严谨证明。

信息学中，一般都**打表**来不严谨地证明！

## 例题 HDU-3480

### 思路

1.  先排序。
2.  $dp_{i,j}$表示前$j$个数，划分为$i$段的最小代价。
3.  答案$dp_{m,n}$。
4.  转移$dp_{i,j}=\min(dp_{i,j},dp_{i-1,k}+(a[j]-a[k+1])^2)$。
5.  初始$dp_{0,0}=0$，其余正无穷。
6.  用四边形不等式优化即可。

### 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=1e4+5,M=5e3+5;
int n,m,dp[M][N],pos[M][N],a[N];

int Work()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	sort(a+1,a+n+1);
	memset(dp,0x3f,sizeof dp);
	dp[0][0]=0;
	for(int i=1;i<=m;i++)
	{
		dp[i][i]=0;
		pos[i][i]=i;
		pos[0][i]=1;
		pos[i][n+1]=n;
		for(int j=n;j>i;j--)
			for(int k=pos[i-1][j];k<=pos[i][j+1];k++)
				if(dp[i][j]>dp[i-1][k-1]+(a[j]-a[k])*(a[j]-a[k]))
					dp[i][j]=dp[i-1][k-1]+(a[j]-a[k])*(a[j]-a[k]),pos[i][j]=k;
	}
	return dp[m][n];
}

int main()
{
	int T;
	cin>>T;
	for(int i=1;i<=T;i++)
		cout<<"Case "<<i<<": "<<Work()<<"\n";
	return 0;
}
```