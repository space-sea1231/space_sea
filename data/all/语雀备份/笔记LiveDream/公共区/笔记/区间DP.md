### 区间DP的一般表达式：

枚举区间长度

枚举区间起点

计算区间终点

枚举区间断点

## P1220 关路灯

### 状态

dp[i][j][0/1]表示区间[i,j]的路灯全关掉且站在i或j处的最小功耗

### 答案

`min(dp[1][n][0],dp[1][n][1])`

### 状态转移

```cpp
for(int len=2;len<=n;len++){
	for(int i=1;i+len-1<=n;i++){ // 起点 
		int j=i+len-1;
		dp[i][j][0]=min(dp[i+1][j][0]+(x[i+1]-x[i])/*时间*/*(sum[i]+sum[n]-sum[j])/*功率之和*/,dp[i+1][j][1]+(x[j]-x[i])/*时间*/*(sum[i]+sum[n]-sum[j])/*功率之和*/);
		dp[i][j][1]=min(dp[i][j-1][0]+(x[j]-x[i])/*时间*/*(sum[i-1]+sum[n]-sum[j-1])/*功率之和*/,dp[i][j-1][i]+(x[j]-x[j-1])/*时间*/*(sum[i-1]+sum[n]-sum[j-1])/*功率之和*/);
	}
}
```

### 初始状态

`dp[i][i]=abs(x[i]-x[c])*(sum[n]-w[c])`

## P4290 [HAOI2008] 玩具取名

### 样例解释

| 初始 | 过程1 | 结果 |
| --- | --- | --- |
| I | WW | IIII |
| N | WW | IIII |

### 状态

dp[i][j][0/1/2/3]表示字符串区间[i,j]的字串可以由第0/1/2/3的字母替换而来。

### 辅助状态

yes[a][b][c]代表a可以用b和c替代。

### 答案

dp[1][n][0]输出w,dp[1][n][1]输出i ……

### 状态转移

```cpp
for(int k=i;k<j;k++){
	for(int c1=0;c1<4;c1++){
		for(int c2=0;c2<4;c2++){
			for(int c=0;c<4;c++){
				if(dp[i][k][c1] && dp[k+1][j][c2]&&yes[c][c1][c2]){
					dp[i][j][c]=1;
				}
			}
		}
	}
}
```

### 初始状态

`dp[i][i][s[i]]=1`

## P1435 [IOI2020] 回文子串

### 状态

dp[i][j]表示将区间[i,j]变成回文的最小操作次数；

### 答案

`dp[i][n];`

### 状态转移

```cpp
dp[i][j]=min(dp[i+1][j],dp[i][j-1])+1;
if(s[i]==s[j]){
	dp[i][j]=min(dp[i][j],dp[i+1][j-1]);
	if(len==2)dp[i][j]=0;
}
```

## P1070 [NOIP2009 普及组] 道路游戏

### 状态

dp[i][j]表示时间为i,机器人处于位置j的到的最大金币数

### 状态转移

情况1：不换机器人

`dp[i][j]=dp[i-1][j-1]+a[i][j]`

情况2:更换机器人

`dp[i][j]=max(dp[i-1][k]+a[i][j]-b[j],dp[i][j])`

## P1775 石子合并（弱化版）

### 状态

dp[i][j]表示从合并i到j所花费的最小代价

### 答案

`dp[1][n]`

### 状态转移

```cpp
dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j]+sum[j]-sum[i-1]);
```

## CF607B Zuma

### 状态

dp[i][j]表示从i到j消除的最小时间

### 状态转移

```cpp
for(int len=3;len<=n;len++){
    for(int i=1;i<=n-len+1;i++){
        int j=i+len-1;
        if(a[i]==a[j])dp[i][j]=dp[i+1][j-1];
        for(int k=i;k<j;k++){
            dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j]);
        }
    }
}
```

## P3205[HNOI2010]合唱队

### 状态

dp[i][j][0/1]表示构成i到j的理想队形从左边来或从右边来的最小操作数

### 状态转移

```cpp
if(h[i]<h[i+1]){
    dp[i][j][0]+=dp[i+1][j][0];
}
if(h[i]<h[j]){
    dp[i][j][0]+=dp[i+1][j][1];
}
if(h[j]>h[i]){
    dp[i][j][1]+=dp[i][j-1][0];
}
if(h[j]>h[j-1]){
    dp[i][j][1]+=dp[i][j-1][1];
}
```

  

### 状态

dp[i][j]表示从i到j的最大权值，g[i][j]表示从i到j的最小权值

/